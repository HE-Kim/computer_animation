// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	char_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("char_mesh"));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset(TEXT("StaticMesh'/Game/character/main/falling_mesh_02.falling_mesh_02'"));

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
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	char_mesh->SetSimulatePhysics(true);
	char_mesh->SetMassOverrideInKg(NAME_None, 40.0f);


	char_mesh->GetBodyInstance()->bLockXRotation = true;
	char_mesh->GetBodyInstance()->bLockYRotation = true;
	char_mesh->GetBodyInstance()->bLockZRotation = true;
	char_mesh->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

	if (camera_actor)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(camera_actor);
		char_to_cam = camera_actor->GetActorLocation() - char_mesh->GetComponentLocation();
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;

	FVector com = char_mesh->GetCenterOfMass();

	FVector F(0.f, 0.f, 200.f);

	FRotator cur_R = char_mesh->GetComponentRotation();
	F = cur_R.RotateVector(F);

	char_mesh->AddForce(F);

	if (camera_actor)
	{
		FVector world_p = char_mesh->GetComponentLocation();
		//FQuat world_q = FQuat(bird_mesh->GetComponentRotation());
		//camera_actor->SetActorLocationAndRotation(world_p, world_q);
		camera_actor->SetActorLocation(world_p + char_to_cam);
		//camera_actor->SetActorRelativeRotation(q);
	}
}

