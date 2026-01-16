// GluckSeligkeit


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ARPGAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UARPGAttributeSet* ARPGAttributeSet = CastChecked<UARPGAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(ARPGAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ARPGAttributeSet->GetMaxHealth());

}
