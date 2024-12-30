// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectileHitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UProjectileHitInterface : public UInterface
{
	GENERATED_BODY()
};

class CYRUS365_ASSIGNMENT_API IProjectileHitInterface
{
	GENERATED_BODY()

public:
	virtual void GetHit(const FVector& ImpactPoint, float DamageAmount) = 0;
};
