#include "SFPlayer.h"

ASFPlayer::ASFPlayer()
{
}

void ASFPlayer::BeginPlay()
{
	Super::BeginPlay();

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