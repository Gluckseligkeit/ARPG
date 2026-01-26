// GluckSeligkeit


#include "AbilitySystem/ARPGAbilitySystemGlobals.h"

#include "ARPGAbilityTypes.h"

FGameplayEffectContext* UARPGAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FARPGGameplayEffectContext();
}
