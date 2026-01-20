// GluckSeligkeit


#include "AbilitySystem/ARPGAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/ARPGWidgetController.h"
#include "Player/ARPGPlayerState.h"
#include "UI/HUD/ARPGHUD.h"

UOverlayWidgetController* UARPGAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AARPGHUD* ARPGHUD = Cast<AARPGHUD>(PC->GetHUD()))
		{
			AARPGPlayerState* PS = PC->GetPlayerState<AARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return ARPGHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UARPGAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AARPGHUD* ARPGHUD = Cast<AARPGHUD>(PC->GetHUD()))
		{
			AARPGPlayerState* PS = PC->GetPlayerState<AARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return ARPGHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
