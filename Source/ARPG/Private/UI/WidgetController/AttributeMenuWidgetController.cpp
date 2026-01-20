// GluckSeligkeit


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/ARPGAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "ARPGGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UARPGAttributeSet* AS = CastChecked<UARPGAttributeSet>(AttributeSet);
	for (auto& Pair: AS->TagToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
[this, Pair, AS](const FOnAttributeChangeData& Data)
		{
			FARPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
			Info.AttributeValue = Pair.Value().GetNumericValue(AS);
			AttributeInfoDelegate.Broadcast(Info);
		}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UARPGAttributeSet* AS = CastChecked<UARPGAttributeSet>(AttributeSet);
	
	check(AttributeInfo);
	
	for (auto& Pair: AS->TagToAttributes)
	{
		FARPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}

}
