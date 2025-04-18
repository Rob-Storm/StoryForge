#include "Item.h"


#include "UObject/ConstructorHelpers.h"
#include "SFCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("WorldModel");
	RootComponent = StaticMeshComponent;

	ItemName = FText::FromString("Item Name");
	ItemDescription = FText::FromString("A brief item description.");	

	
	if (WorldModel == nullptr || StaticMeshComponent->GetStaticMesh() == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube1.Cube1'"));

		if (CubeMesh.Succeeded())
		{
			WorldModel = CubeMesh.Object;

			StaticMeshComponent->SetStaticMesh(WorldModel);
		}
	}
}

#if WITH_EDITOR

void AItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AItem, WorldModel))
	{
		if (WorldModel && StaticMeshComponent)
		{
			StaticMeshComponent->SetStaticMesh(WorldModel);
		}
	}
}

#endif

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact_Implementation(AActor* CallingActor)
{
	ASFCharacter* Character = Cast<ASFCharacter>(CallingActor);

	if(Character)
	{
		if (Character->InventoryComponent->CanAddItem(this))
		{
			Character->InventoryComponent->AddItem(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Added item to inventory"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Cannot add item to inventory"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Cast failed"));
	}
}