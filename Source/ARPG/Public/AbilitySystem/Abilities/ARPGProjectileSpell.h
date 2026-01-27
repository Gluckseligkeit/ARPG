// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGDamageGameplayAbility.h"
#include "ARPGProjectileSpell.generated.h"

class AARPGProjectile;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class ARPG_API UARPGProjectileSpell : public UARPGDamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AARPGProjectile> ProjectileClass;
	
};
