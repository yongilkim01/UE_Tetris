// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/Board.h"

#include "Data/MyDataAsset.h"

#include "Block/BlockPiece.h"
#include "Block/Block.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABoard::BeginPlay()
{
	Super::BeginPlay();

    if (BoardSize != nullptr)
    {
        BoardWidth = BoardSize->Width;
        BoardHeight = BoardSize->Height;

        // TetrisMap이 비어 있으면 먼저 크기를 할당
        TetrisMap.SetNum(BoardWidth);

        // 각 행에 대해 세로 크기 설정 및 초기화
        for (int x = 0; x < BoardWidth; x++)
        {
            TetrisMap[x].SetNum(BoardHeight); // 각 행에 대해 세로 크기 설정

            // 빈 공간으로 초기화
            for (int y = 0; y < BoardHeight; y++)
            {
                TetrisMap[x][y] = 0; // 초기값 (빈 공간)
            }
        }

        CreateBoardEdge(BoardWidth, BoardHeight);

        ABlock* Block = Cast<ABlock>(GetWorld()->SpawnActor<AActor>(BlockClass, FVector::ZeroVector, FRotator::ZeroRotator));
        Block->Board = this;
        Block->InitBlock();
    }
	
}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::CreateBoardEdge(int Width, int Height)
{
    // 액터 크기
    const float BlockSize = UTetrisConst::BlockSize;

    // 맵의 중앙을 기준으로 X, Y 범위 설정
    float StartX = 0.0f;
    float StartY = -((Height * BlockSize) / 2);

    // 상단 (y == -Height / 2), 비우고, 다른 곳에 배치
    for (int x = -Width / 2; x <= Width / 2; x++)  // Width 범위에 맞춰서
    {
        FVector TopLocation = FVector(StartX + x * BlockSize, 0 - (Height / 2) * BlockSize, 0);  // 상단
        SpawnBlockPiece(TopLocation);
    }

    // 하단 (y == Height / 2), 비우고, 다른 곳에 배치
    //for (int x = -Width / 2; x <= Width / 2; x++)  // Width 범위에 맞춰서
    //{
    //    FVector BottomLocation = FVector(StartX + x * BlockSize, 0 + (Height / 2) * BlockSize, 0);  // 하단
    //    SpawnBlockPiece(BottomLocation);
    //}

    // 좌측 (x == -Width / 2), 상단 하단 제외하고 배치
    for (int y = 1; y <= Height; y++)  // 상단 제외, 하단 제외
    {
        FVector LeftLocation = FVector(StartX - (Width / 2) * BlockSize, StartY + y * BlockSize, 0);  // 좌측
        SpawnBlockPiece(LeftLocation);
    }

    // 우측 (x == Width / 2), 상단 하단 제외하고 배치
    for (int y = 1; y <= Height; y++)  // 상단 제외, 하단 제외
    {
        FVector RightLocation = FVector(StartX + (Width / 2) * BlockSize, StartY + y * BlockSize, 0);  // 우측
        SpawnBlockPiece(RightLocation);
    }
}



void ABoard::SpawnBlockPiece(const FVector& Location)
{
    // 액터를 해당 위치에 생성
    AActor* NewActor = GetWorld()->SpawnActor<AActor>(BlockPieceClass, Location, FRotator::ZeroRotator);

    if (NewActor)
    {
        // 필요한 추가 초기화가 있다면 여기에 작성
    }
}
