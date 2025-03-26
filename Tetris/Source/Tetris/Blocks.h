// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyData.h"
#include "Blocks.generated.h"


class ABlock;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UStaticMeshComponent;

class UDataTable;
class UMyDataAsset;



UCLASS()
class TETRIS_API ABlocks : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
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

	UPROPERTY(EditDefaultsOnly)
	UInputAction* GameEndAction;

	void InitBlock();
	void GetBlockOffset(const FName& BlockType);
	bool IsAllBlocksDestroyed();

	void SetBlock(const FInputActionValue& Value);
	void CheckMoveable(const FVector& Dir);
	void CheckRotateable(const FRotator& Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")

	TArray<UStaticMeshComponent*> MeshComponents;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	UDataTable* BlockOffsetTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	UMyDataAsset* MapSize;


	EBlockType BlockType = EBlockType::I;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	TArray<ABlock*> BlockArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	TSubclassOf<ABlock> BlockClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	TSubclassOf<ABlocks> BlocksClass;


};
