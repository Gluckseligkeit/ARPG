// GluckSeligkeit


#include "ARPGGameplayTags.h"
#include "GameplayTagsManager.h"

FARPGGameplayTags FARPGGameplayTags::GameplayTags;

void FARPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases melee damage and carry capacity."));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("Increases attack speed, movement speed, and evasion."));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magic damage and effect potency."));
	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("Increases critical chance, armor penetration, and ranged damage."));
	GameplayTags.Attributes_Primary_Constitution = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Constitution"), FString("Increases max health and physical defense."));
	GameplayTags.Attributes_Primary_Wisdom = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Wisdom"), FString("Increases max mana, magic resistance, and cooldown reduction."));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum amount of health points."));
GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum amount of mana points."));
GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxStamina"), FString("Maximum amount of stamina points."));
GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Amount of health recovered per second."));
GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Amount of mana recovered per second."));
GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRegeneration"), FString("Amount of stamina recovered per second."));
GameplayTags.Attributes_Secondary_MeleeAttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MeleeAttackPower"), FString("Raw damage dealt with melee weapons."));
GameplayTags.Attributes_Secondary_RangedAttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.RangedAttackPower"), FString("Raw damage dealt with ranged weapons."));
GameplayTags.Attributes_Secondary_MagicPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicPower"), FString("Raw damage dealt with spells."));
GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Percentage chance to deal a critical hit."));
GameplayTags.Attributes_Secondary_CriticalDamageMultiplier = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalDamageMultiplier"), FString("Bonus damage multiplier for critical hits."));
GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces physical damage taken."));
GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores a portion of enemy armor."));
GameplayTags.Attributes_Secondary_PhysicalResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalResistance"), FString("Percentage reduction of incoming physical damage."));
GameplayTags.Attributes_Secondary_PhysicalPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalPenetration"), FString("Ignores a portion of enemy physical resistance."));
GameplayTags.Attributes_Secondary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicResistance"), FString("Percentage reduction of incoming magic damage."));
GameplayTags.Attributes_Secondary_MagicPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicPenetration"), FString("Ignores a portion of enemy magic resistance."));
GameplayTags.Attributes_Secondary_AccuracyRating = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AccuracyRating"), FString("Increases chance to hit evasive or distant enemies."));
GameplayTags.Attributes_Secondary_EvasionRating = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.EvasionRating"), FString("Chance to completely avoid an incoming attack."));
GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"), FString("Increases the speed of weapon attacks."));
GameplayTags.Attributes_Secondary_CastSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CastSpeed"), FString("Reduces the time required to cast spells."));
GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"), FString("Speed of character movement."));
GameplayTags.Attributes_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CooldownReduction"), FString("Reduces the cooldown time of abilities."));
	
//InputTags

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_MMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.MMB"), FString("Input Tag for Middle Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for 1 Key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for 2 Key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for 3 Key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for 4 Key"));
	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.5"), FString("Input Tag for 5 Key"));



}



