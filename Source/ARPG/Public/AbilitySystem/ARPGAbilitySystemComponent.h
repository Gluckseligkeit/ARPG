// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ARPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	
	void AbilityActorInfoSet();
	
protected:
	
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
