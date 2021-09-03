// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_house.generated.h"

UCLASS()
class HW_4_API AMyActor_house : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_house();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* char_mesh;

	float time;
};
