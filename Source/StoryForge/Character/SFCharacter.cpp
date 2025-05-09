#include "SFCharacter.h"

#include "Components\CapsuleComponent.h"
#include "GameFramework\CharacterMovementComponent.h"

ASFCharacter::ASFCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

	GetMesh()->bOwnerNoSee = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASFCharacter::SetCurrentItem_Implementation(AItem* Item)
{
	FString DebugMessage = FString::Printf(TEXT("Current Item: %s"), *(Item->ItemName.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, DebugMessage);
}

void ASFCharacter::Die_Implementation()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->PlayAnimation(DeathAnimation, false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OnDie.Broadcast();
}
