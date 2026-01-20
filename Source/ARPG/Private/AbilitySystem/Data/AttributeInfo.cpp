// GluckSeligkeit


#include "AbilitySystem/Data/AttributeInfo.h"

FARPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FARPGAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find INFO for Attribute Tag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FARPGAttributeInfo();
}
