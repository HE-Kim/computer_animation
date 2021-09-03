// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_brid.generated.h"

UCLASS()
class HW_4_API AMyActor_brid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_brid();

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	FTransform GetSplineIterp(float t);

	              
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		USceneComponent* root;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* bird_mesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key0;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key3;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key4;

	UPROPERTY(EditAnywhere)
		float t0;
	UPROPERTY(EditAnywhere)
		float t1;
	UPROPERTY(EditAnywhere)
		float t2;
	UPROPERTY(EditAnywhere)
		float t3;
		UPROPERTY(EditAnywhere)
		float t4;



	UPROPERTY(EditAnywhere)
		AActor* camera_actor;
	UPROPERTY(EditAnywhere)
		AActor* camera_actor2;
	UPROPERTY(EditAnywhere)
		AActor* camera_actor3;

	FVector bird_to_cam;

	float time;
};
