#include "StoryForge/Character/SFPlayer.h"

#include "SFDecoration.h"

ASFDecoration::ASFDecoration()
{
	PrimaryActorTick.bCanEverTick = true;

	WorldModel = CreateDefaultSubobject<UStaticMeshComponent>("WorldModel");
	RootComponent = WorldModel;

	if (DecorationModel == nullptr || WorldModel->GetStaticMesh() == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube1.Cube1'"));

		if (CubeMesh.Succeeded())
		{
			DecorationModel = CubeMesh.Object;

			WorldModel->SetStaticMesh(DecorationModel);
		}
	}
}


#if WITH_EDITOR

void ASFDecoration::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASFDecoration, DecorationModel))
	{
		if (DecorationModel && WorldModel)
		{
			WorldModel->SetStaticMesh(DecorationModel);
		}
	}
}

#endif


void ASFDecoration::BeginPlay()
{
	Super::BeginPlay();
}

void ASFDecoration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASFDecoration::Interact_Implementation(AActor* CallingActor)
{
	ASFPlayer* Player = Cast<ASFPlayer>(CallingActor);

	if(Player && Player->CanPickupDecoration())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Can pick up decoration"));

		Player->PickupDecoration(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Can NOT pick up decoration"));
	}
}
