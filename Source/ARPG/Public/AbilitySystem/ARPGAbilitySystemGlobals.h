// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "ARPGAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
