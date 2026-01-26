// GluckSeligkeit


#include "AbilitySystem/ExecutionCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "ARPGAbilityTypes.h"
#include "ARPGGameplayTags.h"
#include "AbilitySystem/ARPGAbilitySystemLibrary.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct ARPGDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(EvasionChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamageMultiplier);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamageResistance);

	
	ARPGDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, EvasionChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, CriticalDamageResistance, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, PhysicalPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, MagicPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, CriticalDamageMultiplier, Source, false);

	}
};

static const ARPGDamageStatics& DamageStatics()
{
	static ARPGDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().EvasionChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageMultiplierDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageResistanceDef);

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	//Get Damage Set By Caller Mag
	
	float Damage = Spec.GetSetByCallerMagnitude(FARPGGameplayTags::Get().Damage);
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	//float OriginalDamage = Damage;
	
	//DefineCrit
	
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.0f);
	
	float SourceCriticalDamageMultiplier = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageMultiplierDef, EvaluationParameters, SourceCriticalDamageMultiplier);
	SourceCriticalDamageMultiplier = FMath::Max<float>(SourceCriticalDamageMultiplier, 0.0f);
	
	float TargetCriticalDamageResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageResistanceDef, EvaluationParameters, TargetCriticalDamageResistance);
	TargetCriticalDamageResistance = FMath::Max<float>(TargetCriticalDamageResistance, 0.0f);
	
	const bool bCriticalHit = FMath::RandRange(1, 100) < SourceCriticalHitChance;
	
	UARPGAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);
	
	if (bCriticalHit) Damage *= (SourceCriticalDamageMultiplier - TargetCriticalDamageResistance) / 100.f;
	
	//Capture Evasion on Target
	
	float TargetEvasionChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().EvasionChanceDef, EvaluationParameters, TargetEvasionChance);
	TargetEvasionChance = FMath::Max<float>(TargetEvasionChance, 0.0f);
	
	const bool bEvaded = FMath::RandRange(1, 100) < TargetEvasionChance;
	if (bEvaded) Damage *= 0.0f;
	
	//Capture BlockChance on Target
	//If block, halve damage.
	
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.0f);
	
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	
	UARPGAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	
	if (bBlocked) Damage *= 0.5f;
	//Damage = bBlocked ? Damage / 2.0f : Damage;
		
	//Penetration
	
	float SourcePhysicalPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalPenetrationDef, EvaluationParameters, SourcePhysicalPenetration);
	SourcePhysicalPenetration = FMath::Max<float>(SourcePhysicalPenetration, 0.0f);
	
	float SourceMagicPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicPenetrationDef, EvaluationParameters, SourceMagicPenetration);
	SourceMagicPenetration = FMath::Max<float>(SourceMagicPenetration, 0.0f);
	
	//TODO Coeficient
	
	//const UCharacterClassInfo* CHaracterClassInfo = UARPGAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	//const FRealCurve* PhysicalPenetrationCurve = CHaracterClassInfo->DamageCalculationCoefficients->FindCurve(FName("PhysicalPenetration"), FString());
	//const float PhysicalPenetrationCoefficient = PhysicalPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//Resistance magic/phys
	
	float TargetPhysicalResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalResistanceDef, EvaluationParameters, TargetPhysicalResistance);
	TargetPhysicalResistance = FMath::Max<float>(TargetPhysicalResistance, 0.0f);
	
	float TargetMagicResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluationParameters, TargetMagicResistance);
	TargetMagicResistance = FMath::Max<float>(TargetMagicResistance, 0.0f);
	
	const float EffectivePhysicalResistance = TargetPhysicalResistance * ( 100 - SourcePhysicalPenetration) / 100.f;
	Damage *= ( 100 - EffectivePhysicalResistance ) / 100.f;

	const FGameplayModifierEvaluatedData EvaluatedData(UARPGAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
