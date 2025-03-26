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

    // TetrisMap�� ��� ������ ���� ũ�⸦ �Ҵ�
    TetrisMap.SetNum(MapSize->Width);

    // �� �࿡ ���� ���� ũ�� ���� �� �ʱ�ȭ
    for (int x = 0; x < MapSize->Width; x++)
    {
        TetrisMap[x].SetNum(MapSize->Height); // �� �࿡ ���� ���� ũ�� ����

        // �� �������� �ʱ�ȭ
        for (int y = 0; y < MapSize->Height; y++)
        {
            TetrisMap[x][y] = 0; // �ʱⰪ (�� ����)
        }
    }
}

}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}