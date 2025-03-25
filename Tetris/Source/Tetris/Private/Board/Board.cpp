// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/Board.h"

#include "Data/BoardDetaAsset.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	if (MapSize != nullptr)
	{
		SetActorScale3D(FVector(MapSize->Width, MapSize->Height, 1));
	}
	
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
