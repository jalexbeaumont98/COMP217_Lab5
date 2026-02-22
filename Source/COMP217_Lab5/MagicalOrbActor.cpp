// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicalOrbActor.h"

// Sets default values
AMagicalOrbActor::AMagicalOrbActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
	OrbMesh->SetupAttachment(Root);

	OrbLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("OrbLight"));
	OrbLight->SetupAttachment(Root);

	OrbLight->Intensity = 5000.f;
	OrbLight->bUseInverseSquaredFalloff = false;

	RotationRate = FRotator(0.f, 90.f, 0.f);
	PulseSpeed = 2.f;

}

// Called when the game starts or when spawned
void AMagicalOrbActor::BeginPlay()
{
	Super::BeginPlay();

	if (OrbMesh && OrbMesh->GetMaterial(0))
	{
		DynamicMaterial = OrbMesh->CreateDynamicMaterialInstance(0);
	}

	UE_LOG(LogTemp, Warning, TEXT("Magical Orb spawned at %s"),
		*GetActorLocation().ToString());
	
}

// Called every frame
void AMagicalOrbActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RotationRate * DeltaTime);

	if (OrbLight)
	{
		float NewIntensity = 3000.f +
			2000.f * FMath::Sin(GetWorld()->GetTimeSeconds() * PulseSpeed);

		OrbLight->SetIntensity(NewIntensity);
	}

	if (DynamicMaterial)
	{
		float Hue = FMath::Fmod(GetWorld()->GetTimeSeconds() * 50.f, 360.f);

		FLinearColor NewColor =
			FLinearColor::MakeFromHSV8((uint8)Hue, 255, 255);

		DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), NewColor);
	}

}

void AMagicalOrbActor::ToggleLight(bool bEnable)
{
	if (OrbLight)
		OrbLight->SetVisibility(bEnable);
}

void AMagicalOrbActor::SetRotationRate(FRotator NewRate)
{
	RotationRate = NewRate;
}

void AMagicalOrbActor::SetOrbColor(FLinearColor NewColor)
{
	if (DynamicMaterial)
		DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), NewColor);
}

FVector AMagicalOrbActor::GetActorLocationCustom() const
{
	return GetActorLocation();
}

void AMagicalOrbActor::SetActorLocationCustom(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}