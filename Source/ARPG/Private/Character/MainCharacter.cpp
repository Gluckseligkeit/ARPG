// GluckSeligkeit


#include "Character/MainCharacter.h"
#include "AbilitySystemComponent.h"
#include "ARPGGameplayTags.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "ARPG/ARPG.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectiles, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AMainCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AMainCharacter::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MultiCastHandleDeath();
}

void AMainCharacter::MultiCastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	bDead = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AMainCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	//TODO Improve this adding data driven sockets
	const FARPGGameplayTags& GameplayTags = FARPGGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	return FVector();
}

bool AMainCharacter::IsDead_Implementation() const
{
	return bDead; 
}

AActor* AMainCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AMainCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

void AMainCharacter::InitAbilityActorInfo()
{
	
}

void AMainCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle );
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AMainCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AMainCharacter::AddCharacterAbilities()
{
	UARPGAbilitySystemComponent* ARPGASC = CastChecked<UARPGAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	
	ARPGASC->AddCharacterAbilities(StartupAbilities);
}

void AMainCharacter::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		
		StartDissolveTimeline(DynamicMatInst);
		
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}
