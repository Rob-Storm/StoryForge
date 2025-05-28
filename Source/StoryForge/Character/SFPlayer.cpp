#include "SFPlayer.h"

#include "StoryForge/DamageHelper.h"

ASFPlayer::ASFPlayer()
{
    GameCamera = CreateDefaultSubobject<UCameraComponent>("Camera");

    FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

    GameCamera->AttachToComponent(RootComponent, AttachmentRules);
}

void ASFPlayer::BeginPlay()
{
	Super::BeginPlay();

    QuickSlot.SetNum(10);
}

void ASFPlayer::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    FVector ImpactVelocity = GetVelocity();

    if (Hit.GetActor() && Hit.GetActor()->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Damage landed");

        IDamageable::Execute_Damage(Hit.GetActor(), this, UDamageHelper::GetDamageVelocity(ImpactVelocity, 0.f, 0.2f));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Invalid actor hit or actor does not implement idamageable");
    }

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Landed");
}

void ASFPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASFPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ASFPlayer::CanEquipItem()
{
	return !HeldDecoration;
}

bool ASFPlayer::CanPickupDecoration()
{
	return !CurrentItem && !HeldDecoration;
}

void ASFPlayer::PickupDecoration_Implementation(ASFDecoration* DecorationActor)
{

}

void ASFPlayer::DropDecoration_Implementation(bool BreakOnLanding)
{
}

FVector ASFPlayer::GetItemDropVector(bool IsThrowing)
{
    float DropStrength = IsThrowing ? 1000 : 300;
    FVector DropVector;

    if (IsThrowing)
    {
        DropVector = GameCamera->GetForwardVector() * DropStrength;
    }
    else
    {
        DropVector = (GameCamera->GetForwardVector() * DropStrength) + FVector::UpVector * DropStrength / 2;
    }

    return DropVector;
}

TArray<FVector> ASFPlayer::GetActorBoundingBoxCorners(const AActor* Actor, float Padding)
{
	TArray<FVector> Corners;

	if (!Actor)
	{
		return Corners;
	}

	FVector Origin, Extent;

	Actor->GetActorBounds(true, Origin, Extent);

    Extent *= Padding;

    for (int32 XSign = -1; XSign <= 1; XSign += 2)
    {
        for (int32 YSign = -1; YSign <= 1; YSign += 2)
        {
            for (int32 ZSign = -1; ZSign <= 1; ZSign += 2)
            {
                Corners.Add(Origin + FVector(XSign * Extent.X, YSign * Extent.Y, ZSign * Extent.Z));
            }
        }
    }

	return Corners;
}

bool ASFPlayer::GetActorBoundsAsScreenCoords(AActor* Actor, APlayerController* PlayerController, float Padding, FVector2D& OutScreenPosition, FVector2D& OutScreenSize)
{
    if (!Actor || !PlayerController)
    {
        return false;
    }

    TArray<FVector> Corners = GetActorBoundingBoxCorners(Actor, Padding);
    TArray<FVector2D> ScreenPoints;

    for (const FVector& Corner : Corners)
    {
        FVector2D ScreenPos;
        if (PlayerController->ProjectWorldLocationToScreen(Corner, ScreenPos))
        {
            ScreenPoints.Add(ScreenPos);
        }
    }

    if (ScreenPoints.Num() == 0)
    {
        return false;
    }

    FVector2D Min = ScreenPoints[0];
    FVector2D Max = ScreenPoints[0];

    for (const FVector2D& Point : ScreenPoints)
    {
        Min.X = FMath::Min(Min.X, Point.X);
        Min.Y = FMath::Min(Min.Y, Point.Y);
        Max.X = FMath::Max(Max.X, Point.X);
        Max.Y = FMath::Max(Max.Y, Point.Y);
    }

    OutScreenPosition = Min;
    OutScreenSize = Max - Min;
    return true;
}

void ASFPlayer::ThrowCurrentItem()
{
    if (HeldDecoration)
    {
        DropDecoration(false);
    }

    if (!CurrentItem)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Not holding an item"));
        return;
    }

    FTransform DroppedTransform;

    InventoryComponent->DropItem(CurrentItem, DroppedTransform);

    CurrentItem = nullptr;

}

TArray<AItem*> ASFPlayer::SetHotbarSlotItem_Implementation(int32 Slot, AItem* Item)
{
    if (!QuickSlot.IsValidIndex(Slot))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("not valid hotbar slot"));
        return QuickSlot;
    }

    QuickSlot[Slot] = Item;

    return QuickSlot;
}

void ASFPlayer::EquipItemFromSlot(int32 Slot)
{
    if (!QuickSlot.IsValidIndex(Slot) || !QuickSlot[Slot])
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("not valid hotbar slot"));
        return;
    }

    SetCurrentItem(QuickSlot[Slot]);

}

bool ASFPlayer::GetFirstEmptySlot(int32& Slot)
{
    for (int32 i = 0; i < QuickSlot.Num(); i++)
    {
        if (!QuickSlot[i])
        {
            Slot = i;
            return true;
        }
    }

    return false;
}
