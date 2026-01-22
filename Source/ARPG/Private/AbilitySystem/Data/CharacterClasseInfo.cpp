// GluckSeligkeit


#include "AbilitySystem/Data/CharacterClasseInfo.h"

FCharacterCLassDefautInfo UCharacterClasseInfo::GetClassDefautInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
	
}
