// GluckSeligkeit


#include "AbilitySystem/Data/AttributeInfo.h"
#include "GameplayTagsManager.h" // Required for fetching tags

FARPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
    for (const FARPGAttributeInfo& Info : AttributeInformation)
    {
       if (Info.AttributeTag.MatchesTagExact(AttributeTag))
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

// --- NEW CODE START ---

void UAttributeInfo::FillAttributeInfo()
{
    // 1. Get the Tag Manager
    UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

    // 2. Request ALL registered tags into the container
    // (The previous error was here: we were trying to request specific tags incorrectly)
    FGameplayTagContainer TagContainer;
    Manager.RequestAllGameplayTags(TagContainer, true);

    // 3. Define the "Root" tag we are looking for (Attributes)
    FGameplayTag AttributeRootTag = FGameplayTag::RequestGameplayTag(FName("Attributes"));

    // 4. Clear existing data
    AttributeInformation.Empty();

    // 5. Iterate over every single tag in the engine
    for (const FGameplayTag& Tag : TagContainer)
    {
        // Check if the tag is a child of "Attributes" (e.g. Attributes.Primary.Strength)
        // MatchesTag returns true if 'Tag' is the RootTag OR a descendant of RootTag.
        if (Tag.MatchesTag(AttributeRootTag))
        {
            // Skip the "Attributes" root tag itself, we only want the actual stats
            if (Tag.MatchesTagExact(AttributeRootTag)) continue;

            FARPGAttributeInfo Info;
            Info.AttributeTag = Tag;

            // --- Generate Name (e.g., "Attributes.Primary.Strength" -> "Strength") ---
            FString TagNameString = Tag.GetTagName().ToString();
            FString CleanName;
            
            // Split from the end to get the last part
            TagNameString.Split(TEXT("."), nullptr, &CleanName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
            
            // Fallback if no dot is found
            if (CleanName.IsEmpty())
            {
                CleanName = TagNameString;
            }
            
            Info.AttributeName = FText::FromString(CleanName);

            // --- Fetch Description ---
            TSharedPtr<FGameplayTagNode> TagNode = Manager.FindTagNode(Tag);
            if (TagNode.IsValid())
            {
                 Info.AttributeDescription = FText::FromString(TagNode->GetDevComment());
            }

            AttributeInformation.Add(Info);
        }
    }
    
    // 6. Mark asset dirty to save changes
    MarkPackageDirty();
}