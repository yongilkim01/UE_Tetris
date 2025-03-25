// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrisStruct.generated.h"

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
