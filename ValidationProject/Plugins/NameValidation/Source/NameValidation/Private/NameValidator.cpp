/**
 * NameValidator.cpp
 * @author Bram Reuling
 * @date 25/10/2022
 * @brief Base validator class. Will read data from settings file and will do validation based on that.
 */


#include "NameValidator.h"

#include "NameValidationSettings.h"

// TODO: Clean this class up.

bool UNameValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	// Get the settings.
	const UNameValidationSettings* ValidationSettings = GetDefault<UNameValidationSettings>();

	// Check if the validators list has any validators in it.
	if (ValidationSettings->Validators.IsEmpty()) return false;
	
	// Loop over the validator list that we got from the settings.
	for (const auto ValidationInfo : ValidationSettings->Validators)
	{
		// Get the names of the asset class and the validation class.
		FString AssetClassName = InAsset->GetClass()->GetName();
		FString ValidationClassName = ValidationInfo.AssetType->GetName();
		
		// If the asset class and the validation class names are the same, return true.
		if (AssetClassName == ValidationClassName)
		{
			return true;
		}
	}

	return false;
}

EDataValidationResult UNameValidator::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
	// Get the settings.
	const UNameValidationSettings* ValidationSettings = GetDefault<UNameValidationSettings>();
	
	// Loop over the validator list that we got from the settings.
	for (const auto ValidationInfo : ValidationSettings->Validators)
	{
		// Get the names of the asset class and the validation class.
		FString AssetClassName = InAsset->GetClass()->GetName();
		FString ValidationClassName = ValidationInfo.AssetType->GetName();

		// If the asset class and the validation class names are the same, do the validation checks.
		if (AssetClassName == ValidationClassName)
		{
			if (InAsset->GetName().StartsWith(ValidationInfo.ExpectedPrefix))
			{
				AssetPasses(InAsset);
				return EDataValidationResult::Valid;
			}
			else
			{
				AssetFails(InAsset, FText::Format(NSLOCTEXT("NameValidation", "AssetPrefixMissing", "Asset is missing the following prefix: {0}"), FText::FromString(ValidationInfo.ExpectedPrefix)), ValidationErrors);
				return EDataValidationResult::Invalid;
			}
		}
	}

	AssetWarning(InAsset, FText::FromString("Cannot check asset because validator list is empty"));
	return EDataValidationResult::NotValidated;
}
