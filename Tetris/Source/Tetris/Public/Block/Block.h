// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Global/TetrisConst.h"
#include "Global/TetrisStruct.h"

#include "Data/MyData.h"

#include "Block.generated.h"

class UStaticMeshComponent;
class UDataTable;
class UInputMappingContext;
class UInputAction;
class ABlockPiece;
class ABoard;
struct FInputActionValue;

UCLASS()
class TETRIS_API ABlock : public APawn
{
	GENERATED_BODY()

public:
	ABlock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(const FInputActionValue& Value);
	void MoveDown(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);

	void RotateLeft(const FInputActionValue& Value);
	void RandomBlock(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveUpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveDownAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveLeftAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* RotateLeftAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* RandomBlockAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* SetAction;

	void InitBlock();
	void InitBlockPiece();
	void GetBlockOffset(const FName& BlockType);
	bool IsAllBlocksDestroyed();

	void SetBlock(const FInputActionValue& Value);
	void TranslateBlock(const FVector& Dir);
	void RotateBlock(const FRotator& Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")

	TArray<UStaticMeshComponent*> MeshComponents;

	ABoard* Board = nullptr;
	FVector2D CurBoardLocation = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	UDataTable* BlockOffsetTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|BlockType")
	EBlockType BlockType = EBlockType::Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|BlockPiece")
	TArray<ABlockPiece*> BlockPieceArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|BlockInfo")
	TArray<FVector> BlockPlaceArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Spawn")
	TSubclassOf<ABlockPiece> BlockPieceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris|Spawn")
	TSubclassOf<ABlock> BlockClass;

};
