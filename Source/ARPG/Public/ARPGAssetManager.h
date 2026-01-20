// GluckSeligkeit

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ARPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	
	static UARPGAssetManager& Get();
	
protected:
	
	virtual void StartInitialLoading() override;
};
