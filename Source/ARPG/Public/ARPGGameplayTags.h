// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * GameplayTags
 * Singleton with native gameplay tags
 */


struct FARPGGameplayTags
{
	
public:
	static const FARPGGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Attributes_Secondary_Armor;
protected:
	
private:
	static FARPGGameplayTags GameplayTags;
	
};

