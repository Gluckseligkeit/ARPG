// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * GameplayTags
 * Singleton with native gameplay tags
 */


struct FARPGGameplayTags
{
	
public:
	static const FARPGGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Damage;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Magical;
	
	FGameplayTag Effects_HitReact;
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Constitution;
	FGameplayTag Attributes_Primary_Wisdom;
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_StaminaRegeneration;
	FGameplayTag Attributes_Secondary_MeleeAttackPower;
	FGameplayTag Attributes_Secondary_RangedAttackPower;
	FGameplayTag Attributes_Secondary_MagicPower;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalDamageMultiplier;
	FGameplayTag Attributes_Secondary_CriticalDamageResistance;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_Ward;
	FGameplayTag Attributes_Resistance_PhysicalResistance;
	FGameplayTag Attributes_Secondary_PhysicalPenetration;
	FGameplayTag Attributes_Resistance_MagicResistance;
	FGameplayTag Attributes_Secondary_MagicPenetration;
	FGameplayTag Attributes_Secondary_Accuracy;
	FGameplayTag Attributes_Secondary_EvasionChance;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_CastSpeed;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_CooldownReduction;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_MMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;
	
	FGameplayTag Abilities_Attack;
	
	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	
private:
	static FARPGGameplayTags GameplayTags;
	
};

