#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Niagara\Classes\NiagaraSystem.h"

#include "StoryForge/Interactable.h"
#include "StoryForge/Damageable.h"

#include "SFDecoration.generated.h"

UCLASS()
class STORYFORGE_API ASFDecoration : public AActor, public IInteractable, public IDamageable
{
	GENERATED_BODY()

	ASFDecoration();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);


public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	FText DecorationName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	bool CanBePickedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decoration")
	bool BreakOnHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	int32 DefaultHealth = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UStaticMesh> DecorationModel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UMaterial> DroppedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UMaterial> PickUpMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UNiagaraSystem> DebrisEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<USoundBase> HitSoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<USoundBase> PushSoundEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UStaticMeshComponent> WorldModel;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	int32 CurrentHealth;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* CallingActor) override;

	virtual void Damage_Implementation(AActor* CallingActor, int32 Damage) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Decoration")
	void ChangeMaterial(bool PickedUp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Decoration")
	void Break();

	UFUNCTION(BlueprintPure, Category = "Decoration")
	float GetDamageTint();

};