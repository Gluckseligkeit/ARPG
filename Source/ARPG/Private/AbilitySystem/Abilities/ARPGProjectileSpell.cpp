// GluckSeligkeit


#include "AbilitySystem/Abilities/ARPGProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/ARPGProjectile.h"
#include "Interaction/CombatInterface.h"
#include "ARPG/Public/ARPGGameplayTags.h"

void UARPGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UARPGProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		FARPGGameplayTags::Get().Montage_Attack_Weapon);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<AARPGProjectile>(
		ProjectileClass, SpawnTransform, 
		GetOwningActorFromActorInfo(), 
		Cast<APawn>(GetOwningActorFromActorInfo()), 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);
	EffectContextHandle.AddActors(Actors);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
		
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
		
	const FARPGGameplayTags GameplayTags = FARPGGameplayTags::Get();
		
	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);

	}
	Projectile->DamageEffectSpecHandle = SpecHandle;
		
	Projectile->FinishSpawning(SpawnTransform);
};
