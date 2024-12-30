// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetBox.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.h"
#include "Cyrus365_Assignment/Cyrus365_AssignmentCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATargetBox::ATargetBox()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
	ItemMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetGenerateOverlapEvents(true);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

}

void ATargetBox::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.f);
		HealthBarWidget->SetVisibility(false);
	}
}

void ATargetBox::Die()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ACyrus365_AssignmentCharacter* Character = Cast<ACyrus365_AssignmentCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Character->SetScore(score);
	SetLifeSpan(1.f);
}

void ATargetBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetBox::GetHit(const FVector& ImpactPoint, float DamageAmount)
{
	if (Attributes && HealthBarWidget)
	{
		Attributes->RecieveDamage(DamageAmount);
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthpercent());
		HealthBarWidget->SetVisibility(true);
		if (!Attributes->IsAlive()) Die();
	}
}

UStaticMeshComponent* ATargetBox::GetMesh()
{
	return ItemMesh;
}

void ATargetBox::SetScore(int8 value)
{
	score = value;
}

int8 ATargetBox::GetScore()
{
	return score;
}

void ATargetBox::SetMaxhealth(int8 Health)
{
	Attributes->SetMaxHealth(Health);
}

void ATargetBox::SetHealth(int8 Health)
{
	if (Attributes)
	{
		Attributes->SetHealth(Health);
	}
}


