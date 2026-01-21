// GluckSeligkeit


#include "AbilitySystem/Abilities/ARPGProjectileSpell.h"

#include "Actor/ARPGProjectile.h"
#include "Interaction/CombatInterface.h"

void UARPGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UARPGProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		//TODO: Give projectile rotation.
		
		AARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<AARPGProjectile>(
			ProjectileClass, SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetOwningActorFromActorInfo()), 
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		//TODO: Give projectile a gameplay effect for damage.
		
		Projectile->FinishSpawning(SpawnTransform);
	}
};
