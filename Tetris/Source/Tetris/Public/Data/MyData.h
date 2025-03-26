// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FBlockOffSet :public FTableRowBase
{
    GENERATED_BODY()
    FBlockOffSet() {};
    ~FBlockOffSet() {};
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Offset1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Offset2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Offset3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Offset4;
};



UCLASS()
class TETRIS_API UMyData : public UObject
{
    GENERATED_BODY()

};


