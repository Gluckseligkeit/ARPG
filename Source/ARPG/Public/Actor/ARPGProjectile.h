// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGProjectile.generated.h"

UCLASS()
class ARPG_API AARPGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARPGProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
