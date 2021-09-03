// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_tree.generated.h"

UCLASS()
class HW_4_API AMyActor_tree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_tree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree3;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree4;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree5;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* tree6;


	float time;
};
