#include "Weapon.h"

void AWeapon::UseItem_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("bang"));
}