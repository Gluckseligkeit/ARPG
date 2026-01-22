// GluckSeligkeit


#include "ARPGAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "ARPGGameplayTags.h"

UARPGAssetManager& UARPGAssetManager::Get()
{
	check(GEngine)
	UARPGAssetManager* ARPGAssetManager = Cast<UARPGAssetManager>(GEngine->AssetManager);
	return *ARPGAssetManager;
	
}

void UARPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FARPGGameplayTags::InitializeNativeGameplayTags();
	
	//Required to use target data
	UAbilitySystemGlobals::Get().InitGlobalData();
}
