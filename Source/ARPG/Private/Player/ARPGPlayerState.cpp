// GluckSeligkeit


#include "Player/ARPGPlayerState.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

AARPGPlayerState::AARPGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>("AttributeSet");
	
	//Original Code from course
	//NetUpdateFrequency = 100.f;
	//Public access to NetUpdateFrequency has been deprecated. Use SetNetUpdateFrequency() and GetNetUpdateFrequency() instead. - Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	SetNetUpdateFrequency(100.f);
}

void AARPGPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AARPGPlayerState, Level)
}

UAbilitySystemComponent* AARPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AARPGPlayerState::OnRep_Level(int32& OldLevel)
{
	
}
