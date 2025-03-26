// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"
#include "MyDataAsset.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CheckPawn.h"

#include "Block.h"

// Sets default values
AGameMap::AGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameMap::BeginPlay()
{
	Super::BeginPlay();
	if (MapSize != nullptr)
	{
		SetActorRelativeScale3D(FVector( MapSize->Height, MapSize->Width, 1));
		float StartX = (-0.5f * MapSize->Height) * 100.0f+50.0f;
		float StartY = (-0.5f * MapSize->Width) * 100.0f;

		for (int i = 0; i < MapSize->Height; i++)
		{
			ACheckPawn* CheckPawn = GetWorld()->SpawnActor<ACheckPawn>(CheckPawnClass);
			if (CheckPawn)
			{
				CheckPawn->SetActorLocation(FVector(StartX + (i * 100.0f), StartY, 0.0f));
				CheckPawnArray.Add(CheckPawn);
			}
		}
	}
	


}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BlockCheck();
}

void AGameMap::BlockCheck()
{
	int Width = MapSize->Width;
	int Height = MapSize->Height;
	for (ACheckPawn* CheckPawn : CheckPawnArray)
	{
		CheckPawn->CheckLine(Width, Height);
	}
	
}

