// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "Cyrus365_AssignmentGameMode.generated.h"

UCLASS(minimalapi)
class ACyrus365_AssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACyrus365_AssignmentGameMode();

	virtual void StartPlay() override;

	TSharedPtr<FJsonObject> ReadJson(FHttpResponsePtr Response);

	FTargetBoxType ReadTypeStructFromJson(TSharedPtr<FJsonObject> JsonObject);

	FTargetBoxObject ReadObjectStructFromJson(TSharedPtr<FJsonObject> JsonObject);

private:
	void OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	TArray<FTargetBoxType> types;

	TArray<FTargetBoxObject> Objects;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATargetBox> BoxBlueprint;
};

USTRUCT()
struct FTargetBoxType
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString name;

	UPROPERTY()
	int color[3];

	UPROPERTY()
	int32 health;

	UPROPERTY()
	int32 score;
};

USTRUCT()
struct FTransformData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int Location[3];

	UPROPERTY()
	int Rotation[3];

	UPROPERTY()
	int Scale[3];

	FTransformData()
	{
		std::fill(std::begin(Location), std::end(Location), 0);
		std::fill(std::begin(Rotation), std::end(Rotation), 0);
		std::fill(std::begin(Scale), std::end(Scale), 1);
	}
};

USTRUCT()
struct FTargetBoxObject
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString type;

	UPROPERTY()
	FTransformData Transform;
};



