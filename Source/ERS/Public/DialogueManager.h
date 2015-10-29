// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueManager.generated.h"

/**
 * 
 */
UCLASS()
class ERS_API UDialogueManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static TSharedPtr<FJsonObject> jsonObject;
	
	static TArray<FString> ToStringArray(const TArray<TSharedPtr<FJsonValue> > &inArray);

public:
	UDialogueManager(const FObjectInitializer &ObjectInitializer);

	/**
	 * Creates a dialogue JSON
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static void Initialize(FString path);

	/**
	 * Gets the lead-in for a character
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static TArray<FString> GetLeadInDialogue(FString character);

	/**
	 * Gets the lead-out for a character
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static TArray<FString> GetLeadOutDialogue(FString character);

	/**
	 * Gets the number of frames of interaction a character has
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static int32 GetFrameCount(FString character);

	/**
	 * Gets the display for a frame of interaction
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static FString GetFrameDisplay(FString character, int32 frameIndex);

	/**
	 * Gets the number of options for a frame of interaction
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static int32 GetFrameOptionCount(FString character, int32 frameIndex);
	
	/**
	 * Gets the display for an option choice
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static FString GetFrameOptionDisplay(FString character, int32 frameIndex, int32 optionIndex);

	/**
	 * Gets the dialogue array for an option choice
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static TArray<FString> GetFrameOptionDialogue(FString character, int32 frameIndex, int32 optionIndex);

	/**
	 * Gets whether a choice progresses
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static bool GetFrameOptionProgress(FString character, int32 frameIndex, int32 optionIndex);
};
