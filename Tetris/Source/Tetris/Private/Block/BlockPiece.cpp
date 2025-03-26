// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockPiece.h"

// Sets default values
ABlockPiece::ABlockPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

