#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Niagara\Classes\NiagaraSystem.h"

#include "StoryForge/Interactable.h"

#include "SFDecoration.generated.h"

UCLASS()
class STORYFORGE_API ASFDecoration : public AActor, public IInteractable
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
	TObjectPtr<UStaticMesh> DecorationModel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UMaterial> DroppedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UMaterial> PickUpMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UNiagaraSystem> DebrisEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Decoration")
	TObjectPtr<UStaticMeshComponent> WorldModel;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* CallingActor) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Decoration")
	void ChangeMaterial(bool PickedUp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Decoration")
	void Break();

};