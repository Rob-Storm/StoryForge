#pragma once

#include "CoreMinimal.h"
#include "Niagara\Classes\NiagaraSystem.h"

#include "Item/Item.h"

#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAuto UMETA(DisplayName = "Semi-Automatic"),
	Burst UMETA(DisplayName = "Burst Fire"),
	FullAuto UMETA(DisplayName = "Fully-Automatic"),
};

/**
 * 
 */
UCLASS(Abstract)
class STORYFORGE_API AWeapon : public AItem
{
	GENERATED_BODY()

	AWeapon();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Damage = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 CurrentAmmo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MagazineSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Range = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Recoil = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UNiagaraSystem> ShootEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USoundBase> EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USoundBase> ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USoundBase> ReloadStartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USoundBase> ReloadEndSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USoundBase> DryFireSound;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* ShootPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool ShootDelayEnded = true;

	UFUNCTION(BlueprintCallable, Category = "State")
	void ResetDelay();

public:

	virtual void UseItem_Implementation() override;

	virtual void EquipItem_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Shoot();
	
	virtual void Shoot_Implementation();

};
