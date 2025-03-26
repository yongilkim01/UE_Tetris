// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/GameMap.h"

#include "Data/MyDataAsset.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AGameMap::AGameMap()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameMap::BeginPlay()
{
	Super::BeginPlay();

if (MapSize != nullptr)
{
    SetActorRelativeScale3D(FVector(MapSize->Width, MapSize->Height, 1));

    Width = MapSize->Width;
    Height = MapSize->Height;

    // TetrisMap이 비어 있으면 먼저 크기를 할당
    TetrisMap.SetNum(MapSize->Width);

    // 각 행에 대해 세로 크기 설정 및 초기화
    for (int x = 0; x < MapSize->Width; x++)
    {
        TetrisMap[x].SetNum(MapSize->Height); // 각 행에 대해 세로 크기 설정

        // 빈 공간으로 초기화
        for (int y = 0; y < MapSize->Height; y++)
        {
            TetrisMap[x][y] = 0; // 초기값 (빈 공간)
        }
    }
}

}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}