// Fill out your copyright notice in the Description page of Project Settings.


#include "NameValidator.h"

#include "NameValidationSettings.h"


bool UNameValidator::CanValidateAsset_Implementation(UObject* InAsset) const
{
	// Get the settings.
	const UNameValidationSettings* ValidationSettings = GetDefault<UNameValidationSettings>();

	// Check if the validators list has any validators in it.
	if (ValidationSettings->Validators.IsEmpty()) return false;
	
	// Loop over the validator list that we got from the settings.
	for (auto ValidationInfo : ValidationSettings->Validators)
	{
		// Traverse the outer chain of the object and search if it is the type of object the settings contain.
		const UObject* PointerToValidObject = InAsset->GetTypedOuter(ValidationInfo.AssetType);

		// If the type of object was specified in the object, return true.
		if (PointerToValidObject != nullptr)
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
	for (auto ValidationInfo : ValidationSettings->Validators)
	{
		// Traverse the outer chain of the object and search if it is the type of object the settings contain.
		const UObject* PointerToValidObject = InAsset->GetTypedOuter(ValidationInfo.AssetType);

		// If the type of object was specified in the object, return true.
		if (PointerToValidObject != nullptr)
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
