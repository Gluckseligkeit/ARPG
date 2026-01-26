// GluckSeligkeit


#include "AbilitySystem/ARPGAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "ARPGGameplayTags.h"
#include "AssetDefinitionAssetInfo.h"
#include "NiagaraValidationRule.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MainPlayerController.h"

UARPGAttributeSet::UARPGAttributeSet()
{
	const FARPGGameplayTags& GameplayTags = FARPGGameplayTags::Get();
	
	//Primary Attributes	

	TagToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Agility, GetAgilityAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Constitution, GetConstitutionAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Wisdom, GetWisdomAttribute);
	
	//Secondary Attributes
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_StaminaRegeneration, GetStaminaRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MeleeAttackPower, GetMeleeAttackPowerAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_RangedAttackPower, GetRangedAttackPowerAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MagicPower, GetMagicPowerAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalDamageMultiplier, GetCriticalDamageMultiplierAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalDamageResistance, GetCriticalDamageResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_Ward, GetWardAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_PhysicalResistance, GetPhysicalResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_PhysicalPenetration, GetPhysicalPenetrationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MagicResistance, GetMagicResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MagicPenetration, GetMagicPenetrationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_Accuracy, GetAccuracyAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_EvasionChance, GetEvasionChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_AttackSpeed, GetAttackSpeedAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CastSpeed, GetCastSpeedAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MovementSpeed, GetMovementSpeedAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CooldownReduction, GetCooldownReductionAttribute);
	
}

void UARPGAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Constitution, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Wisdom, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MeleeAttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, RangedAttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MagicPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalDamageMultiplier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalDamageResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Ward, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, PhysicalPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MagicPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Accuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, EvasionChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CastSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);

}

void UARPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UARPGAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//Source = Causer of Effect, Target = Target of effect
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
		
	}
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UARPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data,Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Health changed %s health is now %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			
			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FARPGGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			
			ShowFloatingText(Props, LocalIncomingDamage);
			
		}
	}
}

void UARPGAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter);
		}
	}
}

//Vital
void UARPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Health, OldHealth);
}
void UARPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxHealth, OldMaxHealth);
}

void UARPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Mana, OldMana);
}
void UARPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxMana, OldMaxMana);
}

void UARPGAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Stamina, OldStamina);
}

void UARPGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxStamina, OldMaxStamina);
}

//Primary

void UARPGAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Strength, OldStrength);
}
void UARPGAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Agility, OldAgility);
}
void UARPGAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Intelligence, OldIntelligence);
}
void UARPGAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Dexterity, OldDexterity);
}
void UARPGAttributeSet::OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Constitution, OldConstitution);
}
void UARPGAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Wisdom, OldWisdom);
}

//Secondary

void UARPGAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UARPGAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UARPGAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, StaminaRegeneration, OldStaminaRegeneration);
}

void UARPGAttributeSet::OnRep_MeleeAttackPower(const FGameplayAttributeData& OldMeleeAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MeleeAttackPower, OldMeleeAttackPower);
}

void UARPGAttributeSet::OnRep_RangedAttackPower(const FGameplayAttributeData& OldRangedAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, RangedAttackPower, OldRangedAttackPower);
}

void UARPGAttributeSet::OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MagicPower, OldMagicPower);
}

void UARPGAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UARPGAttributeSet::OnRep_CriticalDamageMultiplier(const FGameplayAttributeData& OldCriticalDamageMultiplier) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalDamageMultiplier, OldCriticalDamageMultiplier);
}

void UARPGAttributeSet::OnRep_CriticalDamageResistance(const FGameplayAttributeData& OldCriticalDamageResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalDamageResistance, OldCriticalDamageResistance);
}

void UARPGAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Armor, OldArmor);
}

void UARPGAttributeSet::OnRep_Ward(const FGameplayAttributeData& OldWard) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Ward, OldWard);
}

void UARPGAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UARPGAttributeSet::OnRep_PhysicalPenetration(const FGameplayAttributeData& OldPhysicalPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, PhysicalPenetration, OldPhysicalPenetration);
}

void UARPGAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MagicResistance, OldMagicResistance);
}

void UARPGAttributeSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MagicPenetration, OldMagicPenetration);
}

void UARPGAttributeSet::OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Accuracy, OldAccuracy);
}

void UARPGAttributeSet::OnRep_EvasionChance(const FGameplayAttributeData& OldEvasionChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, EvasionChance, OldEvasionChance);
}

void UARPGAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, BlockChance, OldBlockChance);
}

void UARPGAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UARPGAttributeSet::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CastSpeed, OldCastSpeed);
}

void UARPGAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UARPGAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CooldownReduction, OldCooldownReduction);
}