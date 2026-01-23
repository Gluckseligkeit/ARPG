// GluckSeligkeit


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterCLassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
	
}
