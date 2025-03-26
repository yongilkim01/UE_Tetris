// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameMap.generated.h"

class UMyDataAsset;

UCLASS()
class TETRIS_API AGameMap : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyDataAsset* MapSize;

	float Width = 0.0f;
	float Height = 0.0f;

	TArray<TArray<int>> TetrisMap;
};
