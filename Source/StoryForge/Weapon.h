#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class STORYFORGE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Recoil;

public:

	virtual void UseItem_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void Shoot();
};
