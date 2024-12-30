// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreComponent.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "string"

void UScoreComponent::SetScoreWidgetValue(int32 score)
{
	if (ScoreWidget == nullptr)
	{
		ScoreWidget = Cast<UScoreWidget>(GetUserWidgetObject());
	}

	if (ScoreWidget && ScoreWidget->Value)
	{
		FString ScoreString = FString::FromInt(score);
		FText ScoreText = FText::FromString(ScoreString);
		ScoreWidget->Value->SetText(ScoreText);
	}
}
