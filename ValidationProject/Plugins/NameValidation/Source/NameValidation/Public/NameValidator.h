/**
 * NameValidator.h
 * @author Bram Reuling
 * @date 25/10/2022
 * @brief Base validator class. Will read data from settings file and will do validation based on that.
 */

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "NameValidator.generated.h"

/**
 * 
 */
UCLASS()
class NAMEVALIDATION_API UNameValidator : public UEditorValidatorBase
{
	GENERATED_BODY()
	
public:
	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors) override;
};
