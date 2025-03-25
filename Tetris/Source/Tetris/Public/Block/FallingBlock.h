// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Global/TetrisConst.h"
#include "Global/TetrisStruct.h"

#include "FallingBlock.generated.h"

UCLASS()
class TETRIS_API AFallingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitBlockInfo();
	void InitBlockMeshes();

private:
	UPROPERTY(EditAnywhere, Category = "Block")
	TArray<UStaticMeshComponent*> BlockMeshes;

	TArray<FBlockInfo> Tetrominoes;

	UMaterialInterface* BlockMaterial;


};
