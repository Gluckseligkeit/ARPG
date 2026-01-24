// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
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
	virtual void Die() override;

	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere ,BlueprintReadOnly, Category= "Combat")
	float LifeSpan = 5.f;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Mage;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

private:
	

	
};
