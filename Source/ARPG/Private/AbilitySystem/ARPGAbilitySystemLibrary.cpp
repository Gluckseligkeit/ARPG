// GluckSeligkeit


#include "AbilitySystem/ARPGAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/ARPGGameMode.h"
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

void UARPGAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AARPGGameMode* ARPGGameMode = Cast<AARPGGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ARPGGameMode == nullptr) return;
	
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = ARPGGameMode->CharacterClassInfo;
	FCharacterCLassDefaultInfo ClassDefaultInfo = ARPGGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle ASC->MakeEffectContext()
	
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttribute, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttribute, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
