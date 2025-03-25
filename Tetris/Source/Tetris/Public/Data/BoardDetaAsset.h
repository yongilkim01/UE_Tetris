// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BoardDetaAsset.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API UBoardDetaAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height = 1;
	
};
