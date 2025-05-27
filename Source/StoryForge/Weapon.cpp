#include "Weapon.h"

#include "StoryForge\Damageable.h"

#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetSystemLibrary.h"
#include "TimerManager.h"


AWeapon::AWeapon()
{
	ShootPoint = CreateDefaultSubobject<USceneComponent>("ShootPoint");

	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	ShootPoint->AttachToComponent(RootComponent, AttachmentRules);
}

void AWeapon::Shoot_Implementation()
{
	if (!ShootDelayEnded)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("wait bitch"));
		return;
	}

	if (CurrentAmmo <= 0)
	{
		UGameplayStatics::PlaySound2D(this, DryFireSound);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("no ammo"));

		return;
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ShootSound);

		CurrentAmmo--;
		ShootDelayEnded = false;

		FVector Start = ShootPoint->GetComponentLocation();
		FVector End = Start + (ShootPoint->GetForwardVector() * Range);

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		FHitResult OutHit;

		UKismetSystemLibrary::LineTraceSingle
		(
			this,
			Start,
			End,
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::Persistent,
			OutHit,
			true
		);

		AActor* OutHitActor = OutHit.GetActor();

		if (OutHitActor && OutHitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			IDamageable::Execute_Damage(OutHitActor, this, Damage);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hit something"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hit nothing or thing is not damageable"));
		}

		FTimerHandle ShootDelayTimerHandle;

		GetWorldTimerManager().SetTimer
		(
			ShootDelayTimerHandle,
			this,
			&AWeapon::ResetDelay, 
			FireRate, 
			false
		);
	}
}

void AWeapon::ResetDelay()
{
	ShootDelayEnded = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("can shoot again"));

}

void AWeapon::UseItem_Implementation()
{
	Shoot();
}

void AWeapon::EquipItem_Implementation()
{
	UGameplayStatics::PlaySound2D(this, EquipSound);
}