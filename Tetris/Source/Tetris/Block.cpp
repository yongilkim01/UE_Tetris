// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 생성자에서 마테리얼 로드
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(
        TEXT("/Script/Engine.Material'/Game/Level/MT_Block.MT_Block'")
    );

    if (MaterialFinder.Succeeded())
    {
        BlockMaterial = MaterialFinder.Object;
    }

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlock::SetBlockColor(FLinearColor Color)
{
    UStaticMeshComponent* CubeMesh = FindComponentByClass<UStaticMeshComponent>();

    if (CubeMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cube Mesh Found!"));
    }

    if (nullptr != BlockMaterial)
    {
        UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BlockMaterial, this);
        if (DynamicMaterial)
        {
            DynamicMaterial->SetVectorParameterValue(TEXT("ColorParam"), Color);
            CubeMesh->SetMaterial(0, DynamicMaterial);
        }
    }
}



