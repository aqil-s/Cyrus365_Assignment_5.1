// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ScoreComponent.generated.h"

/**
 * 
 */
UCLASS()
class CYRUS365_ASSIGNMENT_API UScoreComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	void SetScoreWidgetValue(int32 score);

private:

	UPROPERTY()
	class UScoreWidget* ScoreWidget;
	
};
