// GluckSeligkeit


#include "UI/HUD/ARPGHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ARPGUserWidget.h"

void AARPGHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//Changed some stuff maybe need to check later
	
	UUserWidget* Widget = CreateWidget<UARPGUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

