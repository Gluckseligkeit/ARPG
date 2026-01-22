// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClasseInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Mage,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterCLassDefautInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};

/**
 * 
 */
UCLASS()
class ARPG_API UCharacterClasseInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defauts")
	TMap<ECharacterClass, FCharacterCLassDefautInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defauts")
	TSubclassOf<UGameplayEffect> SecondaryAttribute;
	
	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defauts")
	TSubclassOf<UGameplayEffect> VitalAttribute;
	
	FCharacterCLassDefautInfo GetClassDefautInfo(ECharacterClass CharacterClass);
};
