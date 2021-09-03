// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_board.h"

// Sets default values
AMyActor_board::AMyActor_board()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	char_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("char_mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset(TEXT("StaticMesh'/Game/character/ect/skateboard_3_.skateboard_3_'"));

	if (mesh_Asset.Succeeded()) {
		UStaticMesh* m1 = mesh_Asset.Object;
		char_mesh->SetStaticMesh(m1);


	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}

	char_mesh->AttachTo(root);
}

// Called when the game starts or when spawned
void AMyActor_board::BeginPlay()
{
	Super::BeginPlay();
	char_mesh->SetSimulatePhysics(true);
	char_mesh->SetMassOverrideInKg(NAME_None, 1.0f);


	char_mesh->GetBodyInstance()->bLockXRotation = true;
	char_mesh->GetBodyInstance()->bLockYRotation = true;
	char_mesh->GetBodyInstance()->bLockZRotation = true;
	char_mesh->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
}

// Called every frame
void AMyActor_board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;

	FVector com = char_mesh->GetCenterOfMass();

	FVector F(0.f, 0.f, 50.f);

	FRotator cur_R = char_mesh->GetComponentRotation();
	F = cur_R.RotateVector(F);

	char_mesh->AddForce(F);
}

