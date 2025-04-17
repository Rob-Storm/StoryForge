#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class STORYFORGE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

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

};
