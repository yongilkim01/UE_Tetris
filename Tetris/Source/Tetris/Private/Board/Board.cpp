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

        // TetrisMap�� ��� ������ ���� ũ�⸦ �Ҵ�
        TetrisMap.SetNum(BoardWidth);

        // �� �࿡ ���� ���� ũ�� ���� �� �ʱ�ȭ
        for (int x = 0; x < BoardWidth; x++)
        {
            TetrisMap[x].SetNum(BoardHeight); // �� �࿡ ���� ���� ũ�� ����

            // �� �������� �ʱ�ȭ
            for (int y = 0; y < BoardHeight; y++)
            {
                TetrisMap[x][y] = 0; // �ʱⰪ (�� ����)
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
    // ���� ũ��
    const float BlockSize = UTetrisConst::BlockSize;

    // ���� �߾��� �������� X, Y ���� ����
    float StartX = 0.0f;
    float StartY = -((Height * BlockSize) / 2);

    // ��� (y == -Height / 2), ����, �ٸ� ���� ��ġ
    for (int x = -Width / 2; x <= Width / 2; x++)  // Width ������ ���缭
    {
        FVector TopLocation = FVector(StartX + x * BlockSize, 0 - (Height / 2) * BlockSize, 0);  // ���
        SpawnBlockPiece(TopLocation);
    }

    // �ϴ� (y == Height / 2), ����, �ٸ� ���� ��ġ
    //for (int x = -Width / 2; x <= Width / 2; x++)  // Width ������ ���缭
    //{
    //    FVector BottomLocation = FVector(StartX + x * BlockSize, 0 + (Height / 2) * BlockSize, 0);  // �ϴ�
    //    SpawnBlockPiece(BottomLocation);
    //}

    // ���� (x == -Width / 2), ��� �ϴ� �����ϰ� ��ġ
    for (int y = 1; y <= Height; y++)  // ��� ����, �ϴ� ����
    {
        FVector LeftLocation = FVector(StartX - (Width / 2) * BlockSize, StartY + y * BlockSize, 0);  // ����
        SpawnBlockPiece(LeftLocation);
    }

    // ���� (x == Width / 2), ��� �ϴ� �����ϰ� ��ġ
    for (int y = 1; y <= Height; y++)  // ��� ����, �ϴ� ����
    {
        FVector RightLocation = FVector(StartX + (Width / 2) * BlockSize, StartY + y * BlockSize, 0);  // ����
        SpawnBlockPiece(RightLocation);
    }
}



void ABoard::SpawnBlockPiece(const FVector& Location)
{
    // ���͸� �ش� ��ġ�� ����
    AActor* NewActor = GetWorld()->SpawnActor<AActor>(BlockPieceClass, Location, FRotator::ZeroRotator);

    if (NewActor)
    {
        // �ʿ��� �߰� �ʱ�ȭ�� �ִٸ� ���⿡ �ۼ�
    }
}
