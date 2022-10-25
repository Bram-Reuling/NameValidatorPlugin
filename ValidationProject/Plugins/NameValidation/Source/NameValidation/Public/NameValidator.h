// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "NameValidationSettings.h"
#include "NameValidator.generated.h"

/**
 * 
 */
UCLASS()
class NAMEVALIDATION_API UNameValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

	TSubclassOf<UObject> ValidObject;
	
public:
	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors) override;
};
