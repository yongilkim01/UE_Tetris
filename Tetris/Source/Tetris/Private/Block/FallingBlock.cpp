// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/FallingBlock.h"

AFallingBlock::AFallingBlock()
{
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    Tetrominoes = {
        // I 블록 (색상은 파란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(3, 0, 0)
            },
            FLinearColor::Blue
        },

        // O 블록 (색상은 노란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0)
            },
            FLinearColor::Yellow
        },

        // T 블록 (색상은 보라색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(1, 1, 0)
            },
            FLinearColor(128.0f, 0.0f, 128.0f)  // 퍼플 색상 (RGB: 128, 0, 128)
        },

        // S 블록 (색상은 초록색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Green
        },

        // Z 블록 (색상은 빨간색)
        FBlockInfo{
            {
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0)
            },
            FLinearColor::Red
        },

        // J 블록 (색상은 파란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Blue
        },

        // L 블록 (색상은 주황색)
        FBlockInfo{
            {
                FVector(2, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor(255.0f, 165.0f, 0.0f)  // 오렌지 색상 (RGB: 255, 165, 0)
        }
    };

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
        TEXT("StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'")
    );

    for (int i = 0; i < UTetrisConst::BlockCount; i++)
    {
        // 새로운 StaticMeshComponent 생성
        UStaticMeshComponent* BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockMesh" + FString::FromInt(i + 1)));
        BlockMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        BlockMesh->SetStaticMesh(CubeMesh.Object);
        // BlockMeshes 배열에 추가
        BlockMeshes.Add(BlockMesh);

    }

    // 생성자에서 마테리얼 로드
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

        // 색상 적용
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

        // 오프셋을 적용하여 월드 위치 설정
        FVector DeltaLocation = SelectedBlockInfo.BlockOffsets[i] * 50.0f; // 기준 위치 + 오프셋
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
        // I 블록 (색상은 파란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(3, 0, 0)
            },
            FLinearColor::Blue
        },

        // O 블록 (색상은 노란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0)
            },
            FLinearColor::Yellow
        },

        // T 블록 (색상은 보라색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0),
                FVector(1, 1, 0)
            },
            FLinearColor(128 / 255.0f, 0 / 255.0f, 128 / 255.0f)  // 퍼플 색상 (RGB: 128, 0, 128)
        },

        // S 블록 (색상은 초록색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(1, 0, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Green
        },

        // Z 블록 (색상은 빨간색)
        FBlockInfo{
            {
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(1, 0, 0),
                FVector(2, 0, 0)
            },
            FLinearColor::Red
        },

        // J 블록 (색상은 파란색)
        FBlockInfo{
            {
                FVector(0, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
            FLinearColor::Blue
        },

        // L 블록 (색상은 주황색)
        FBlockInfo{
            {
                FVector(2, 0, 0),
                FVector(0, 1, 0),
                FVector(1, 1, 0),
                FVector(2, 1, 0)
            },
             FLinearColor(255 / 255.0f, 165 / 255.0f, 0 / 255.0f)  // 오렌지 색상 (RGB: 255, 165, 0)
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
        // 새로운 StaticMeshComponent 생성
        UStaticMeshComponent* BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockMesh" + FString::FromInt(i + 1)));
        BlockMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        // 메쉬 할당
        BlockMesh->SetStaticMesh(CubeMesh.Object);

        // 색상 적용
        //BlockMesh->SetMaterial(0, CreateMaterialWithColor(SelectedBlock.Color));

        // BlockMeshes 배열에 추가
        BlockMeshes.Add(BlockMesh);

        // 오프셋을 적용하여 월드 위치 설정
        FVector DeltaLocation = SelectedBlockInfo.BlockOffsets[i] * 50.0f; // 기준 위치 + 오프셋
        BlockMesh->SetRelativeLocation(DeltaLocation);

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
            FString::Printf(TEXT("Block Position: %s"), *DeltaLocation.ToString()));
    }
}
