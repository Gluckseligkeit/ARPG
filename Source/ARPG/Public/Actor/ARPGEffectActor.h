// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class ARPG_API AARPGEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffect;
	
private:
};
