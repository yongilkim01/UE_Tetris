// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/FallingBlock.h"

AFallingBlock::AFallingBlock()
{
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    Tetrominoes = {
        // I ��� (������ �Ķ���)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(3, 0, 0)
            },
            FLinearColor::Blue
        },

        // O ��� (������ �����)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0)
            },
            FLinearColor::Yellow
        },

        // T ��� (������ �����)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(1, 1, 0)
            },
            FLinearColor(128.0f, 0.0f, 128.0f)  // ���� ���� (RGB: 128, 0, 128)
        },

        // S ��� (������ �ʷϻ�)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Green
        },

        // Z ��� (������ ������)
        FBlockInfo{
            {
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0)
            },
            FLinearColor::Red
        },

        // J ��� (������ �Ķ���)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Blue
        },

        // L ��� (������ ��Ȳ��)
        FBlockInfo{
            {
                FVector(2, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor(255.0f, 165.0f, 0.0f)  // ������ ���� (RGB: 255, 165, 0)
        }
    };

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
        TEXT("StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'")
    );

    for (int i = 0; i < UTetrisConst::BlockCount; i++)
    {
        // ���ο� StaticMeshComponent ����
        UStaticMeshComponent* BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockMesh" + FString::FromInt(i + 1)));
        BlockMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        BlockMesh->SetStaticMesh(CubeMesh.Object);
        // BlockMeshes �迭�� �߰�
        BlockMeshes.Add(BlockMesh);

    }

    // �����ڿ��� ���׸��� �ε�
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(
        TEXT("/Script/Engine.Material'/Game/Materials/MT_Block.MT_Block'")
    );

    if (MaterialFinder.Succeeded())
    {
        BlockMaterial = MaterialFinder.Object;
    }
}

void AFallingBlock::BeginPlay()
{
	Super::BeginPlay();

    int32 RandomBlockType = FMath::RandRange(0, Tetrominoes.Num() - 1);

    FBlockInfo SelectedBlockInfo = Tetrominoes[RandomBlockType];

    FVector CurLocation = GetActorLocation();

    for (int32 i = 0; i < BlockMeshes.Num(); i++)
    {

        // ���� ����
        //BlockMesh->SetMaterial(0, CreateMaterialWithColor(SelectedBlock.Color));

        if (nullptr != BlockMaterial)
        {
            UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BlockMaterial, this);
            if (DynamicMaterial)
            {
                DynamicMaterial->SetVectorParameterValue(TEXT("ColorParam"), SelectedBlockInfo.Color);
                BlockMeshes[i]->SetMaterial(0, DynamicMaterial);
            }
        }

        // �������� �����Ͽ� ���� ��ġ ����
        FVector DeltaLocation = SelectedBlockInfo.BlockOffsets[i] * 50.0f; // ���� ��ġ + ������
        BlockMeshes[i]->SetRelativeLocation(DeltaLocation);

    }

    SetActorLocation(CurLocation);
	
}

void AFallingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFallingBlock::InitBlockInfo()
{
    Tetrominoes = {
        // I ��� (������ �Ķ���)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(3, 0, 0)
            },
            FLinearColor::Blue
        },

        // O ��� (������ �����)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0)
            },
            FLinearColor::Yellow
        },

        // T ��� (������ �����)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(1, 1, 0)
            },
            FLinearColor(128 / 255.0f, 0 / 255.0f, 128 / 255.0f)  // ���� ���� (RGB: 128, 0, 128)
        },

        // S ��� (������ �ʷϻ�)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Green
        },

        // Z ��� (������ ������)
        FBlockInfo{
            {
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0)
            },
            FLinearColor::Red
        },

        // J ��� (������ �Ķ���)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Blue
        },

        // L ��� (������ ��Ȳ��)
        FBlockInfo{
            {
                FVector(2, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
             FLinearColor(255 / 255.0f, 165 / 255.0f, 0 / 255.0f)  // ������ ���� (RGB: 255, 165, 0)
        }
    };
}

void AFallingBlock::InitBlockMeshes()
{
    int32 RandomBlockType = FMath::RandRange(0, Tetrominoes.Num() - 1);

    FBlockInfo SelectedBlockInfo = Tetrominoes[RandomBlockType];

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
        TEXT("StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'")
    );

    for (int32 i = 0; i < SelectedBlockInfo.BlockOffsets.Num(); i++)
    {
        // ���ο� StaticMeshComponent ����
        UStaticMeshComponent* BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockMesh" + FString::FromInt(i + 1)));
        BlockMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        // �޽� �Ҵ�
        BlockMesh->SetStaticMesh(CubeMesh.Object);

        // ���� ����
        //BlockMesh->SetMaterial(0, CreateMaterialWithColor(SelectedBlock.Color));

        // BlockMeshes �迭�� �߰�
        BlockMeshes.Add(BlockMesh);

        // �������� �����Ͽ� ���� ��ġ ����
        FVector DeltaLocation = SelectedBlockInfo.BlockOffsets[i] * 50.0f; // ���� ��ġ + ������
        BlockMesh->SetRelativeLocation(DeltaLocation);

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
            FString::Printf(TEXT("Block Position: %s"), *DeltaLocation.ToString()));
    }
}
