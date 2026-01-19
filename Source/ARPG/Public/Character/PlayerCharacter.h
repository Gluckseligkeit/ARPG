// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	

	
private:
	virtual void InitAbilityActorInfo() override;
};
