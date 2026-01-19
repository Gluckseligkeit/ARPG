// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AEnemyCharacter : public AMainCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
	//Enemy interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
private:
	

	
};
