// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "ARPGDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGDamageGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
