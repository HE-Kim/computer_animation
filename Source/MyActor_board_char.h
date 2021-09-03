// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_board_char.generated.h"

UCLASS()
class HW_4_API AMyActor_board_char : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_board_char();
	virtual bool ShouldTickIfViewportsOnly() const override;
	FTransform GetSplineIterp(float t);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		USceneComponent* root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key[10];


	UPROPERTY(EditAnywhere)
		float t_arr[10];

	float time;
};
