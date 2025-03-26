// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TetrisGameMode.h"

#include "Board/Board.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	Board = Cast<ABoard>(GetWorld()->SpawnActor<AActor>(BoardClass, FVector::ZeroVector, FRotator::ZeroRotator));
}

void ATetrisGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
