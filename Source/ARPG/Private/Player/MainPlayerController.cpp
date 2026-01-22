// GluckSeligkeit


#include "Player/MainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/ARPGInputComponent.h"
#include "Interaction/EnemyInterface.h"

AMainPlayerController::AMainPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AMainPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AMainPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
	
	
}

void AMainPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FARPGGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AMainPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FARPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag); //weird if in single line
	
	if (!bTargeting && !bAimKeyDown)
	{
		if (GetASC())
		{
			const APawn* ControlledPawn = GetPawn();
			if (FollowTime <= ShortPressTreshold && ControlledPawn)
			{
				if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
				{
					Spline->ClearSplinePoints();
					for (const FVector& PointLoc : NavPath->PathPoints)
					{
						Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					}
					if (NavPath->PathPoints.Num() > 0)
					{
						CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
						bAutoRunning = true;
					}
				}
			}
			FollowTime = 0.f;
			bTargeting = false;		
		}
	}
}

void AMainPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FARPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting || bAimKeyDown)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UARPGAbilitySystemComponent* AMainPlayerController::GetASC()
{
	if (ARPGAbilitySystemComponent == nullptr)
	{
		ARPGAbilitySystemComponent = Cast<UARPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ARPGAbilitySystemComponent;
}



void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UARPGInputComponent* ARPGInputComponent = CastChecked<UARPGInputComponent>(InputComponent);
	ARPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	ARPGInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AMainPlayerController::AimPressed);
	ARPGInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AMainPlayerController::AimReleased);
	ARPGInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AMainPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//If anything bugs with autorunning, this is the culprint
	bAutoRunning = false;
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


