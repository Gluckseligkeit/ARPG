// GluckSeligkeit


#include "Player/ARPGPlayerState.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"

AARPGPlayerState::AARPGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>("AttributeSet");
	
	//Original Code from course
	//NetUpdateFrequency = 100.f;
	//Public access to NetUpdateFrequency has been deprecated. Use SetNetUpdateFrequency() and GetNetUpdateFrequency() instead. - Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AARPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
