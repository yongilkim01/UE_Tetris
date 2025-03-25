// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrisStruct.generated.h"

struct FBlockInfo
{
	TArray<FVector> BlockOffsets;  // �� ����� �������� �����ϴ� �迭
	FLinearColor Color;            // ����� ����
};

/**
 * 
 */
UCLASS()
class TETRIS_API UTetrisStruct : public UObject
{
	GENERATED_BODY()
	
};
