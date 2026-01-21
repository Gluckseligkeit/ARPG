// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ARPG_API AARPGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
