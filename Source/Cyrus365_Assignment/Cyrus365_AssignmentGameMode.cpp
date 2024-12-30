// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cyrus365_AssignmentGameMode.h"
#include "Cyrus365_AssignmentCharacter.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "UObject/ConstructorHelpers.h"
#include "TargetBox.h"

ACyrus365_AssignmentGameMode::ACyrus365_AssignmentGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ACyrus365_AssignmentGameMode::StartPlay()
{
	Super::StartPlay();

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ACyrus365_AssignmentGameMode::OnResponseRecieved);
	Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

TSharedPtr<FJsonObject> ACyrus365_AssignmentGameMode::ReadJson(FHttpResponsePtr Response)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (!FJsonSerializer::Deserialize(Reader, ResponseObj))
	{
		UE_LOG(LogTemp, Display, TEXT("Read JSON failed - was not able to deserialize JSON String"));
		return nullptr;
	}
	UE_LOG(LogTemp, Display, TEXT("Read JSON success!"));
	return ResponseObj;
}

FTargetBoxType ACyrus365_AssignmentGameMode::ReadTypeStructFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	FTargetBoxType TypeStruct;

	if (!FJsonObjectConverter::JsonObjectToUStruct<FTargetBoxType>(JsonObject.ToSharedRef(), &TypeStruct))
	{
		UE_LOG(LogTemp, Display, TEXT("Read type struct JSON failed - was not able to convert JSON object to desired struct"));
		return FTargetBoxType();
	}
	UE_LOG(LogTemp, Display, TEXT("Read type struct JSON success!"));
	return TypeStruct;
}

FTargetBoxObject ACyrus365_AssignmentGameMode::ReadObjectStructFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	FTargetBoxObject ObjectStruct;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FTargetBoxObject>(JsonObject.ToSharedRef(), &ObjectStruct))
	{
		UE_LOG(LogTemp, Display, TEXT("Read object struct JSON failed - was not able to convert JSON object to desired struct"));
		return FTargetBoxObject();
	}
	UE_LOG(LogTemp, Display, TEXT("Read object struct JSON success!"));
	return ObjectStruct;
}

void ACyrus365_AssignmentGameMode::OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{

	TArray<TSharedPtr<FJsonValue>> TypeArray = ReadJson(Response)->GetArrayField("types");

	for (auto obj : TypeArray)
	{
		types.Add(ReadTypeStructFromJson(obj->AsObject()));
	}


	TArray<TSharedPtr<FJsonValue>> ObjectArray = ReadJson(Response)->GetArrayField("objects");

	//UE_LOG(LogTemp, Display, TEXT("%s"), *Response->GetContentAsString());

	for (auto obj : ObjectArray)
	{
		Objects.Add(ReadObjectStructFromJson(obj->AsObject()));
	}
	for (auto obj : types)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *obj.name);
	}
	for (auto obj : Objects)
	{
		FVector Location(obj.Transform.Location[0], obj.Transform.Location[1], obj.Transform.Location[2]);
		FRotator Rotation(obj.Transform.Rotation[0], obj.Transform.Rotation[1], obj.Transform.Rotation[2]);
		FVector Scale(obj.Transform.Scale[0], obj.Transform.Scale[1], obj.Transform.Scale[2]);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATargetBox* BoxActor = GetWorld()->SpawnActor<ATargetBox>(BoxBlueprint, Location, Rotation, SpawnInfo);
		if (BoxActor)
		{
			BoxActor->SetActorScale3D(Scale);
			UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(BoxActor->GetMesh()->GetMaterial(0), NULL);
			FLinearColor BoxColor;
			if (obj.type == FString("RedBox"))
			{
				BoxColor = FLinearColor(types[0].color[0], types[0].color[1], types[0].color[2]);
				material->SetVectorParameterValue(FName(TEXT("Color")), BoxColor);
				BoxActor->GetMesh()->SetMaterial(0, material);
				BoxActor->SetScore(types[0].score);
				BoxActor->SetMaxhealth(types[0].health);
				BoxActor->SetHealth(types[0].health);
			}
			else if (obj.type == FString("BlueBox"))
			{
				BoxColor = FLinearColor(types[1].color[0], types[1].color[1], types[1].color[2]);
				material->SetVectorParameterValue(FName(TEXT("Color")), BoxColor);
				BoxActor->GetMesh()->SetMaterial(0, material);
				BoxActor->SetScore(types[1].score);
				BoxActor->SetMaxhealth(types[1].health);
				BoxActor->SetHealth(types[1].health);
			}
			else if (obj.type == FString("GreenBox"))
			{
				BoxColor = FLinearColor(types[2].color[0], types[2].color[1], types[2].color[2]);
				material->SetVectorParameterValue(FName(TEXT("Color")), BoxColor);
				BoxActor->GetMesh()->SetMaterial(0, material);
				BoxActor->SetScore(types[2].score);
				BoxActor->SetMaxhealth(types[2].health);
				BoxActor->SetHealth(types[2].health);
			}
		}
	}

}
