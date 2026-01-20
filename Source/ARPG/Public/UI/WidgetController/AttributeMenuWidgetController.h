// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ARPGWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UAttributeMenuWidgetController : public UARPGWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
};
