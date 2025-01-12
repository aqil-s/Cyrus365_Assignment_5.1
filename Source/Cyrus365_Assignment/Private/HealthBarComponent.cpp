// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarComponent.h"
#include "HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBar == nullptr)
	{
		HealthBar = Cast<UHealthBar>(GetUserWidgetObject());
	}

	if (HealthBar && HealthBar->HealthBar)
	{
		HealthBar->HealthBar->SetPercent(Percent);
	}
}
