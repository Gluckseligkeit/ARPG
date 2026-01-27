// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MainPlayerController.generated.h"

class UDamageTextComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UARPGInputConfig;
class UARPGAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class ARPG_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainPlayerController();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bCriticalHit, bool bBlockedHit);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AimAction;
	
	void AimPressed() { bAimKeyDown = true; };
	void AimReleased() { bAimKeyDown = false; };
	bool bAimKeyDown = false;
	
	void Move(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	FHitResult CursorHit;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UARPGInputConfig> InputConfig;
	
	UPROPERTY()
	TObjectPtr<UARPGAbilitySystemComponent> ARPGAbilitySystemComponent;
	
	UARPGAbilitySystemComponent* GetASC();
	
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressTreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
