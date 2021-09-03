// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_leaf.generated.h"

UCLASS()
class HW_4_API AMyActor_leaf : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_leaf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		USceneComponent* root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* leaf_mesh;
	
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* leaf_mesh_arr[10];

	float time;


	
};
