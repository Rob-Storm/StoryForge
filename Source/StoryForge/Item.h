#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Item.generated.h"

UCLASS(Abstract)
class STORYFORGE_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AItem();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

public:

	// Fields

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaData")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaData")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UStaticMesh* WorldModel;

	// Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* CallingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void SetItemEnabled(bool ItemEnabled);

};
