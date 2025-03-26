// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TetrisGameMode.generated.h"

class ABoard;

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Board")
	TSubclassOf<ABoard> BoardClass;

	ABoard* Board = nullptr;
};
