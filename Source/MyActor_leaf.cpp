// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_leaf.h"

// Sets default values
AMyActor_leaf::AMyActor_leaf()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	leaf_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh"));
	leaf_mesh_arr[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh1"));
	leaf_mesh_arr[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh2"));
	leaf_mesh_arr[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh3"));
	leaf_mesh_arr[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh4"));
	leaf_mesh_arr[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh5"));
	leaf_mesh_arr[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh6"));
	leaf_mesh_arr[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh7"));
	leaf_mesh_arr[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh8"));
	leaf_mesh_arr[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh9"));
	leaf_mesh_arr[9] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leaf_mesh10"));
	

	 //leaf_mesh -> leaf_mesh_arr[0];

	


	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset(TEXT("StaticMesh'/Game/character/tree/leaf_Plane001.leaf_Plane001'"));
	//leaf_mesh_arr[0]= leaf_mesh;

	if (mesh_Asset.Succeeded()) {
		UStaticMesh* m1 = mesh_Asset.Object;
		leaf_mesh->SetStaticMesh(m1);
	
		for (int i = 0; i < 10; i++)
		{
			leaf_mesh_arr[i] -> SetStaticMesh(m1);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}

	leaf_mesh->AttachTo(root);
	for (int i = 0; i < 10; i++)
	{
		leaf_mesh_arr[i]->AttachTo(root);
	}

}

// Called when the game starts or when spawned
void AMyActor_leaf::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	


	leaf_mesh->SetSimulatePhysics(true);


	for (int i = 0; i < 10; i++)
	{
		leaf_mesh_arr[i]->SetSimulatePhysics(true);
		leaf_mesh_arr[i]->SetMassOverrideInKg(NAME_None, 0.05f);
		leaf_mesh_arr[i]->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
	}

	leaf_mesh->SetMassOverrideInKg(NAME_None, 0.05f);


	//leaf_mesh->GetBodyInstance()->bLockXRotation = true;
	//leaf_mesh->GetBodyInstance()->bLockYRotation = true;
	//leaf_mesh->GetBodyInstance()->bLockZRotation = true;
	leaf_mesh->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
}

// Called every frame
void AMyActor_leaf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;

	FVector com = leaf_mesh->GetCenterOfMass();

	FVector F(0.f, 0.f, 500.f);

	FRotator cur_R = leaf_mesh->GetComponentRotation();
	F = cur_R.RotateVector(F);

	leaf_mesh->AddForce(F);


	for (int i = 0; i < 10; i++)
	{
		com = leaf_mesh_arr[i]->GetCenterOfMass();

		cur_R = leaf_mesh_arr[i]->GetComponentRotation();
		F = cur_R.RotateVector(F);

		leaf_mesh_arr[i]->AddForce(F);

		
	}
}

