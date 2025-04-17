#include "UObject/ConstructorHelpers.h"

#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("WorldModel");
	RootComponent = StaticMeshComponent;

	ItemName = FText::FromString("Item Name");
	ItemDescription = FText::FromString("A brief item description.");	

	/*
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube1.Cube1'"));
	
	if (CubeMesh.Succeeded())
	{
		WorldModel = CubeMesh.Object;

		StaticMeshComponent->SetStaticMesh(WorldModel);
	}
	*/

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

