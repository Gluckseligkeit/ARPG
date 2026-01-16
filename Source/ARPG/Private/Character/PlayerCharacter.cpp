// GluckSeligkeit


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ARPGPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init actor for the server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init actor for the client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AARPGPlayerState* ARPGPlayerState = GetPlayerState<AARPGPlayerState>();
	check(ARPGPlayerState);
	ARPGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ARPGPlayerState, this);
	AbilitySystemComponent = ARPGPlayerState->GetAbilitySystemComponent();
	AttributeSet = ARPGPlayerState->GetAttributeSet();
}
