// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_board_char.h"

// Sets default values
AMyActor_board_char::AMyActor_board_char()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	key[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key0"));
	key[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key1"));
	key[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key2"));
	key[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key3"));
	key[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key4"));
	key[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key5"));
	key[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key6"));
	key[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key7"));
	key[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key8"));
	key[9] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key9"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset(TEXT("StaticMesh'/Game/character/main/board_mesh_06.board_mesh_06'"));

	if (mesh_Asset.Succeeded()) {

		UStaticMesh* m = mesh_Asset.Object;
		mesh->SetStaticMesh(m);
		for (int i = 0; i < 10; i++)
		{
			key[i]->SetStaticMesh(m);
		}
	}
	mesh->AttachTo(root);
	
	for (int i = 0; i < 10; i++)
	{
		key[i]->AttachTo(root);
		key[i]->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.f), FRotator(0.0f, 0.0f, 0.0f));
		t_arr[i] = i;
	}

}

// Called when the game starts or when spawned
void AMyActor_board_char::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	for (int i = 0; i < 10; i++)
	{
		key[i]->SetVisibility(false);
	}
}
bool AMyActor_board_char::ShouldTickIfViewportsOnly() const
{
	return true;
}

FTransform AMyActor_board_char::GetSplineIterp(float t)
{
	FVector p;
	FQuat q;
	FVector p_arr[10];
	FQuat q_arr[10];
	for (int i = 0; i < 10; i++)
	{
		p_arr[i] = key[i]->GetRelativeLocation();
		q_arr[i] = FQuat(key[i]->GetRelativeRotation());
	}

	if (t < t_arr[0])
	{
		p = p_arr[0];
		q = q_arr[0];
	}
	else if (t < t_arr[1])
	{
		p = FMath::CubicCRSplineInterpSafe(p_arr[0], p_arr[0], p_arr[1], p_arr[2], t_arr[0] - 1.f, t_arr[0], t_arr[1], t_arr[2], t);
		q = FMath::CubicCRSplineInterpSafe(q_arr[0], q_arr[0], q_arr[1], q_arr[2], t_arr[0] - 1.f, t_arr[0], t_arr[1], t_arr[2], t);
	}
	else if (t < t_arr[2])
	{
		p = FMath::CubicCRSplineInterpSafe(p_arr[0], p_arr[1], p_arr[2], p_arr[3], t_arr[0], t_arr[1], t_arr[2], t_arr[3], t);
		q = FMath::CubicCRSplineInterpSafe(q_arr[0], q_arr[1], q_arr[2], q_arr[3], t_arr[0], t_arr[1], t_arr[2], t_arr[3], t);
	}
	else if (t < t_arr[8])
	{
		for (int i = 3; i < 9; i++)
		{
			if (t < t_arr[i])
			{
				p = FMath::CubicCRSplineInterpSafe(p_arr[i - 2], p_arr[i - 1], p_arr[i], p_arr[i + 1], t_arr[i - 2], t_arr[i - 1], t_arr[i], t_arr[i + 1], t);
				q = FMath::CubicCRSplineInterpSafe(q_arr[i - 2], q_arr[i - 1], q_arr[i], q_arr[i + 1], t_arr[i - 2], t_arr[i - 1], t_arr[i], t_arr[i + 1], t);
				break;
			}
		}
	}
	else if (t < t_arr[9])
	{
		p = FMath::CubicCRSplineInterpSafe(p_arr[7], p_arr[8], p_arr[9], p_arr[9], t_arr[7], t_arr[8], t_arr[9], t_arr[9] + 1.f, t);
		q = FMath::CubicCRSplineInterpSafe(q_arr[7], q_arr[8], q_arr[9], q_arr[9], t_arr[7], t_arr[8], t_arr[9], t_arr[9] + 1.f, t);
	}
	else
	{
		p = p_arr[9];
		q = q_arr[9];
	}
	

	FTransform T;

	T.SetLocation(p);
	q.Normalize();
	T.SetRotation(q);

	return T;
}


// Called every frame
void AMyActor_board_char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasActorBegunPlay())
	{
		time += DeltaTime;

		FTransform T = GetSplineIterp(time);

		mesh->SetRelativeTransform(T);
	}

}

