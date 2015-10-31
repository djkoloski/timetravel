// Fill out your copyright notice in the Description page of Project Settings.

#include "ERS.h"
#include "DialogueManager.h"

TSharedPtr<FJsonObject> UDialogueManager::jsonObject;

TArray<FString> UDialogueManager::ToStringArray(const TArray<TSharedPtr<FJsonValue> > &inArray)
{
	TArray<FString> outArray;
	outArray.SetNum(inArray.Num());
	for (int32 i = 0; i < inArray.Num(); ++i)
		outArray[i] = inArray[i]->AsString();
	return outArray;
}

UDialogueManager::UDialogueManager(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDialogueManager::Initialize(FString path)
{
	path = FPaths::GameDir() + path;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to locate JSON file"));
		return;
	}

	FString jsonString;
	FFileHelper::LoadFileToString(jsonString, *path);

	TSharedRef<TJsonReader<> > reader = TJsonReaderFactory<>::Create(jsonString);
	if (FJsonSerializer::Deserialize(reader, jsonObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded JSON successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load JSON"));
	}
}

TArray<FString> UDialogueManager::GetLeadInDialogue(FString character)
{
	return UDialogueManager::ToStringArray(jsonObject->GetObjectField(character)->GetArrayField("leadin"));
}

TArray<FString> UDialogueManager::GetLeadOutDialogue(FString character)
{
	return UDialogueManager::ToStringArray(jsonObject->GetObjectField(character)->GetArrayField("leadout"));
}

int32 UDialogueManager::GetFrameCount(FString character)
{
	return jsonObject->GetObjectField(character)->GetArrayField("frames").Num();
}

FString UDialogueManager::GetFrameDisplay(FString character, int32 frameIndex)
{
	return jsonObject->GetObjectField(character)->GetArrayField("frames")[frameIndex]->AsObject()->GetStringField("display");
}

int32 UDialogueManager::GetFrameOptionCount(FString character, int32 frameIndex)
{
	return jsonObject->GetObjectField(character)->GetArrayField("frames")[frameIndex]->AsObject()->GetArrayField("options").Num();
}

FString UDialogueManager::GetFrameOptionDisplay(FString character, int32 frameIndex, int32 optionIndex)
{
	return jsonObject->GetObjectField(character)->GetArrayField("frames")[frameIndex]->AsObject()->GetArrayField("options")[optionIndex]->AsObject()->GetStringField("display");
}

TArray<FString> UDialogueManager::GetFrameOptionDialogue(FString character, int32 frameIndex, int32 optionIndex)
{
	return UDialogueManager::ToStringArray(jsonObject->GetObjectField(character)->GetArrayField("frames")[frameIndex]->AsObject()->GetArrayField("options")[optionIndex]->AsObject()->GetArrayField("response"));
}

bool UDialogueManager::GetFrameOptionProgress(FString character, int32 frameIndex, int32 optionIndex)
{
	return jsonObject->GetObjectField(character)->GetArrayField("frames")[frameIndex]->AsObject()->GetArrayField("options")[optionIndex]->AsObject()->GetBoolField("progress");
}