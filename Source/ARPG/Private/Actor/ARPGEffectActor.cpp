// GluckSeligkeit


#include "Actor/ARPGEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AARPGEffectActor::AARPGEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AARPGEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AARPGEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO: Change This 
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UARPGAttributeSet* ARPGAttributeSet = Cast<UARPGAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UARPGAttributeSet::StaticClass()));
		UARPGAttributeSet* MutableARPGAttributeSet = const_cast<UARPGAttributeSet*>(ARPGAttributeSet);
		MutableARPGAttributeSet->SetHealth(ARPGAttributeSet->GetHealth() + 10.f);
		MutableARPGAttributeSet->SetMana(ARPGAttributeSet->GetMana() + 10.f);
		Destroy();
	}
}

void AARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AARPGEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AARPGEffectActor::EndOverlap);
}


