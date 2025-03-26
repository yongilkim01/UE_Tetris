// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Global/TetrisConst.h"
#include "Global/TetrisStruct.h"

#include "Board.generated.h"

class UMyDataAsset;
class ABlockPiece;
class ABlock;

UCLASS()
class TETRIS_API ABoard : public APawn
{
	GENERATED_BODY()

public:
	ABoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void CreateBoardEdge(int Width, int Height);
	void SpawnBlockPiece(const FVector& Location);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Board")
	UMyDataAsset* BoardSize = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Board")
	TSubclassOf<ABlockPiece> BlockPieceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Spawn")
	TSubclassOf<ABlock> BlockClass;

public:
	float BoardWidth = 0.0f;
	float BoardHeight = 0.0f;

	TArray<TArray<int>> TetrisMap;

};
