// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_tree.h"

// Sets default values
AMyActor_tree::AMyActor_tree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	tree1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree0"));
	tree2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree1"));
	tree3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree2"));
	tree4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree3"));
	tree5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree4"));
	tree6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree5"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset1(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__8_tree.tree_X12_+X1_Rock_Pack__8_tree'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset2(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__7_tree.tree_X12_+X1_Rock_Pack__7_tree'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset3(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__4_tree.tree_X12_+X1_Rock_Pack__4_tree'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset4(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__5_tree.tree_X12_+X1_Rock_Pack__5_tree'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset5(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__6_tree.tree_X12_+X1_Rock_Pack__6_tree'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh_Asset6(TEXT("StaticMesh'/Game/character/tree/tree_X12_+X1_Rock_Pack__3_tree.tree_X12_+X1_Rock_Pack__3_tree'"));
	if (mesh_Asset1.Succeeded()) {
		UStaticMesh* m1 = mesh_Asset1.Object;
		tree1->SetStaticMesh(m1);
		UStaticMesh* m2 = mesh_Asset2.Object;
		tree2->SetStaticMesh(m2);
		UStaticMesh* m3 = mesh_Asset3.Object;
		tree3->SetStaticMesh(m3);
		UStaticMesh* m4 = mesh_Asset4.Object;
		tree4->SetStaticMesh(m4);
		UStaticMesh* m5 = mesh_Asset5.Object;
		tree5->SetStaticMesh(m5);
		UStaticMesh* m6 = mesh_Asset6.Object;
		tree6->SetStaticMesh(m6);
	}

	tree1->AttachTo(root);
	tree2->AttachTo(root);
	tree3->AttachTo(root);
	tree4->AttachTo(root);
	tree5->AttachTo(root);
	tree6->AttachTo(root);

}

// Called when the game starts or when spawned
void AMyActor_tree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor_tree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

