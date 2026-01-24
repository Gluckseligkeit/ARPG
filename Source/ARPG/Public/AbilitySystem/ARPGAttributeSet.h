// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ARPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY()
	AController* SourceController = nullptr;
	
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY()
	AController* TargetController = nullptr;
	
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename  TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


/**
 * 
 */
UCLASS()
class ARPG_API UARPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UARPGAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagToAttributes;
	
	//PRIMARY ATTRIBUTES
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "PrimaryAttributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Strength);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "PrimaryAttributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Dexterity);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "PrimaryAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Intelligence);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Agility, Category = "PrimaryAttributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Agility);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Constitution, Category = "PrimaryAttributes")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Constitution);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Wisdom, Category = "PrimaryAttributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Wisdom);

	
	//VITAL ATTRIBUTES
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxStamina);

	//MEta
	
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, IncomingDamage);
	
	//secondary
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, StaminaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeAttackPower, Category = "Secondary Attributes")
	FGameplayAttributeData MeleeAttackPower;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MeleeAttackPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedAttackPower, Category = "Secondary Attributes")
	FGameplayAttributeData RangedAttackPower;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, RangedAttackPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPower, Category = "Secondary Attributes")
	FGameplayAttributeData MagicPower;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MagicPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamageMultiplier, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CriticalDamageMultiplier);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, PhysicalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalPenetration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, PhysicalPenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MagicResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData MagicPenetration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MagicPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AccuracyRating, Category = "Secondary Attributes")
	FGameplayAttributeData AccuracyRating;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, AccuracyRating);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EvasionRating, Category = "Secondary Attributes")
	FGameplayAttributeData EvasionRating;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, EvasionRating);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, AttackSpeed);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CastSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CastSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Secondary Attributes")
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CooldownReduction);
	
	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const;
	
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	
	UFUNCTION()
	void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) const;
	
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
	
	UFUNCTION()
	void OnRep_EvasionRating(const FGameplayAttributeData& OldEvasionRating) const;
	
	UFUNCTION()
	void OnRep_AccuracyRating(const FGameplayAttributeData& OldAccuracyRating) const;
	
	UFUNCTION()
	void OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const;
	
	UFUNCTION()
	void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;
	
	UFUNCTION()
	void OnRep_PhysicalPenetration(const FGameplayAttributeData& OldPhysicalPenetration) const;
	
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;
	
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	
	UFUNCTION()
	void OnRep_CriticalDamageMultiplier(const FGameplayAttributeData& OldCriticalDamageMultiplier) const;
	
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	
	UFUNCTION()
	void OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower) const;
	
	UFUNCTION()
	void OnRep_RangedAttackPower(const FGameplayAttributeData& OldRangedAttackPower) const;
	
	UFUNCTION()
	void OnRep_MeleeAttackPower(const FGameplayAttributeData& OldMeleeAttackPower) const;
	
	UFUNCTION()
	void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;
	
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	
	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldAgility) const;
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	
	UFUNCTION()
	void OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const;
	
	UFUNCTION()
	void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const;
	
private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, float Damage) const;
};

