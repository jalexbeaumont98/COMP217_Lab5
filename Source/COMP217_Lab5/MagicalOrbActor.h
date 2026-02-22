// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MagicalOrbActor.generated.h"

UCLASS()
class COMP217_LAB5_API AMagicalOrbActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicalOrbActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ToggleLight(bool bEnable);

	UFUNCTION(BlueprintCallable)
	void SetRotationRate(FRotator NewRate);

	UFUNCTION(BlueprintCallable)
	void SetOrbColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
	FVector GetActorLocationCustom() const;

	UFUNCTION(BlueprintCallable)
	void SetActorLocationCustom(FVector NewLocation);

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OrbMesh;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* OrbLight;

	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere)
	FRotator RotationRate;

	UPROPERTY(EditAnywhere)
	float PulseSpeed;

};
