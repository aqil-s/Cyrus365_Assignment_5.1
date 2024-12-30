// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileHitInterface.h"
#include "TargetBox.generated.h"

UCLASS()
class CYRUS365_ASSIGNMENT_API ATargetBox : public AActor, public IProjectileHitInterface
{
	GENERATED_BODY()
	
public:	

	ATargetBox();

	virtual void Tick(float DeltaTime) override;

	virtual void GetHit(const FVector& ImpactPoint, float DamageAmount) override;

	UStaticMeshComponent* GetMesh();

	void SetScore(int8 value);
	int8 GetScore();

	void SetMaxhealth(int8 Health);
	void SetHealth(int8 Health);

protected:

	virtual void BeginPlay() override;

	void Die();

private:

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere)
	class UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	int8 score;
};
