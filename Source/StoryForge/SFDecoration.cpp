#include "SFDecoration.h"

#include "Kismet/GameplayStatics.h"

#include "StoryForge/Character/SFPlayer.h"

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

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASFDecoration, DroppedMaterial))
	{
		if (DecorationModel && WorldModel)
		{
			WorldModel->GetStaticMesh()->SetMaterial(0, DroppedMaterial);
		}
	}
}

#endif


void ASFDecoration::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;
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

void ASFDecoration::Damage_Implementation(AActor* CallingActor, int32 Damage)
{
	if (Damage <= 0)
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSoundEffect, GetActorLocation());
	}

	CurrentHealth -= Damage;

	if(CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		Break();
	}
}

float ASFDecoration::GetDamageTint()
{
	float FDefaultHealth = (float)DefaultHealth;
	float FCurrentHealth = (float)CurrentHealth;
	float alpha = 1.0f - (FCurrentHealth / FDefaultHealth);
	return FMath::Lerp(0.f, 0.85f, alpha);
}