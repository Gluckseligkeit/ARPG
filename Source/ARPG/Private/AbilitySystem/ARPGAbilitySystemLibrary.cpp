// GluckSeligkeit


#include "AbilitySystem/ARPGAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "ARPGAbilityTypes.h"
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
	
	
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterCLassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttribute, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttribute, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UARPGAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	AARPGGameMode* ARPGGameMode = Cast<AARPGGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ARPGGameMode == nullptr) return;
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UARPGAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AARPGGameMode* ARPGGameMode = Cast<AARPGGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ARPGGameMode == nullptr) return nullptr;
	return ARPGGameMode->CharacterClassInfo;
}

bool UARPGAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FARPGGameplayEffectContext* ARPGEffectContext = static_cast<const FARPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return  ARPGEffectContext->IsBlockedHit();
	}
	return false;
}

bool UARPGAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FARPGGameplayEffectContext* ARPGEffectContext = static_cast<const FARPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return  ARPGEffectContext->IsCriticalHit();
	}
	return false;
}

void UARPGAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlockedHit)
{
	if (FARPGGameplayEffectContext* ARPGEffectContext = static_cast<FARPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ARPGEffectContext->SetIsBlockedHit(bIsBlockedHit);
	}
}

void UARPGAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsCriticalHit)
{
	if (FARPGGameplayEffectContext* ARPGEffectContext = static_cast<FARPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ARPGEffectContext->SetIsCriticalHit(bIsCriticalHit);
	}
};
