// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_brid.h"
#include "DrawDebugHelpers.h"
// Sets default values
AMyActor_brid::AMyActor_brid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	bird_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bird_mesh1"));
	key0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key0"));
	key1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key1"));
	key2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key2"));
	key3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key3"));
	key4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key4"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> bird_Asset(TEXT("StaticMesh'/Game/character/bird/untitled-scene.untitled-scene'"));

	if (bird_Asset.Succeeded()) {

		UStaticMesh* m = bird_Asset.Object;
		bird_mesh->SetStaticMesh(m);
		key0->SetStaticMesh(m);
		key1->SetStaticMesh(m);
		key2->SetStaticMesh(m);
		key3->SetStaticMesh(m);
		key4->SetStaticMesh(m);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}
	bird_mesh->AttachTo(root);
	key0->AttachTo(root);
	key1->AttachTo(root);
	key2->AttachTo(root);
	key3->AttachTo(root);
	key4->AttachTo(root);

	key0->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));
	key1->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));;
	key2->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));
	key3->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));
	key4->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));

	t0 = 0.f;
	t1 = 1.5f;
	t2 = 2.0f;
	t3 = 3.0f;
	t4 = 4.0f;
}

// Called when the game starts or when spawned
void AMyActor_brid::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;


	if (camera_actor)
	{
		//GetWorld()->GetFirstPlayerController()->SetViewTarget(camera_actor);
		//heli_to_cam = camera_actor->GetActorLocation() - key0->GetComponentLocation();
	}if (camera_actor2)
	{
		//GetWorld()->GetFirstPlayerController()->SetViewTarget(camera_actor2);
		//heli_to_cam = camera_actor->GetActorLocation() - key0->GetComponentLocation();
	}if (camera_actor3)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(camera_actor3);
		bird_to_cam = camera_actor3->GetActorLocation() - key0->GetComponentLocation();
	}
	
	key0->SetVisibility(false);
	key1->SetVisibility(false);
	key2->SetVisibility(false);
	key3->SetVisibility(false);
	key4->SetVisibility(false);
}
bool AMyActor_brid::ShouldTickIfViewportsOnly() const
{
	return true;
}

FTransform AMyActor_brid::GetSplineIterp(float t)
{
	FVector p;
	FQuat q;
	FVector p0 = key0->GetRelativeLocation();
	FVector p1 = key1->GetRelativeLocation();
	FVector p2 = key2->GetRelativeLocation();
	FVector p3 = key3->GetRelativeLocation();
	FVector p4 = key4->GetRelativeLocation();
	FQuat q0 = FQuat(key0->GetRelativeRotation());
	FQuat q1 = FQuat(key1->GetRelativeRotation());
	FQuat q2 = FQuat(key2->GetRelativeRotation());
	FQuat q3 = FQuat(key3->GetRelativeRotation());
	FQuat q4 = FQuat(key4->GetRelativeRotation());

	if (t < t0)
	{
		p = p0;
		q = q0;
	}
	else if (t < t1)
	{
		p = FMath::CubicCRSplineInterpSafe(p0, p0, p1, p2, t0 - 1.f, t0, t1, t2, t);
		q = FMath::CubicCRSplineInterpSafe(q0, q0, q1, q2, t0 - 1.f, t0, t1, t2, t);
	}
	else if (t < t2)
	{
		p = FMath::CubicCRSplineInterpSafe(p0, p1, p2, p3, t0, t1, t2, t3, t);
		q = FMath::CubicCRSplineInterpSafe(q0, q1, q2, q3, t0, t1, t2, t3, t);
	}
	else if (t < t3)
	{
		p = FMath::CubicCRSplineInterpSafe(p1, p2, p3, p4, t1, t2, t3, t4, t);
		q = FMath::CubicCRSplineInterpSafe(q1, q2, q3, q4, t1, t2, t3, t4, t);
	}else if (t < t4)
	{
		p = FMath::CubicCRSplineInterpSafe(p2, p3, p4, p4, t2, t3, t4, t4 + 1.f, t);
		q = FMath::CubicCRSplineInterpSafe(q2, q3, q4, q4, t2, t3, t4, t4 + 1.f, t);
	}
	else
	{
		p = p4;
		q = q4;
	}

	FTransform T;

	T.SetLocation(p);
	q.Normalize();
	T.SetRotation(q);

	return T;
}


// Called every frame
void AMyActor_brid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasActorBegunPlay())
	{
		time += DeltaTime;
		FTransform T = GetSplineIterp(time);

		bird_mesh->SetRelativeTransform(T);

		//esh1->SetRelativeLocationAndRotation(p, q);
		if (camera_actor3)
		{
			FVector world_p = bird_mesh->GetComponentLocation();
			//FQuat world_q = FQuat(bird_mesh->GetComponentRotation());
			//camera_actor->SetActorLocationAndRotation(world_p, world_q);
			camera_actor3->SetActorLocation(world_p + bird_to_cam);
			//camera_actor->SetActorRelativeRotation(q);
		}
	}
}

