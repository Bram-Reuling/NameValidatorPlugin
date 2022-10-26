/**
 * NameValidationSettings.h
 * @author Bram Reuling
 * @date 25/10/2022
 * @brief Base class for the plugin settings.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NameValidationSettings.generated.h"

USTRUCT(BlueprintType)
struct FValidationInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	TSubclassOf<UObject> AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FString ExpectedPrefix;
};

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Name Validation Settings"))
class NAMEVALIDATION_API UNameValidationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TArray<FValidationInfo> Validators;

	UNameValidationSettings();
};
