// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ARPGHUD.generated.h"

class UARPGUserWidget;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UARPGUserWidget> OverlayWidget;
	
protected:
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UARPGUserWidget> OverlayWidgetClass;
};
