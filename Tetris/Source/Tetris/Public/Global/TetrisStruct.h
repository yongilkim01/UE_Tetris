// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrisStruct.generated.h"

UENUM(BlueprintType)
enum class EBlockType : uint8
{
    I     UMETA(DisplayName = "I Block", ToolTip = "This is the I-shaped block."),
    J     UMETA(DisplayName = "J Block", ToolTip = "This is the J-shaped block."),
    L     UMETA(DisplayName = "L Block", ToolTip = "This is the L-shaped block."),
    O     UMETA(DisplayName = "O Block", ToolTip = "This is the O-shaped block."),
    S     UMETA(DisplayName = "S Block", ToolTip = "This is the S-shaped block."),
    T     UMETA(DisplayName = "T Block", ToolTip = "This is the T-shaped block."),
    Z     UMETA(DisplayName = "Z Block", ToolTip = "This is the Z-shaped block.")
};

struct FBlockInfo
{
	TArray<FVector> BlockOffsets;  // 각 블록의 오프셋을 저장하는 배열
	FLinearColor Color;            // 블록의 색상
};

/**
 * 
 */
UCLASS()
class TETRIS_API UTetrisStruct : public UObject
{
	GENERATED_BODY()
	
};
