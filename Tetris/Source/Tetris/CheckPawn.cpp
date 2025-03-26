// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPawn.h"
#include "Block.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ACheckPawn::ACheckPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACheckPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACheckPawn::CheckLine(int Width, int Height)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0, Width * 100.0f, 0);

	FCollisionQueryParams QueryParams;
	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByObjectType(
		HitResults,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECC_WorldDynamic),
		QueryParams
		
	);

	

	CurCount = 0;  // Count �ʱ�ȭ ��ġ ����
	TArray<AActor*> ProcessedActors;  // �̹� ó���� Actor�� ������ �迭

	for (FHitResult& HitResult : HitResults)
	{
		if (HitResult.GetActor() && HitResult.GetActor()->IsA<ABlock>())
		{
			ABlock* Block = Cast<ABlock>(HitResult.GetActor());
			if (Block && !ProcessedActors.Contains(Block)) // �̹� ó���� ����� ����
			{
				ProcessedActors.Add(Block);  // ó���� ����� �߰�
				CurCount++;
			}
		}
	}

	if (CurCount == Width)
	{
		// ���� �� ä�����ٸ� �ش� �� ����
		for (FHitResult& HitResult : HitResults)
		{
			ABlock* Block = Cast<ABlock>(HitResult.GetActor());
			if (Block)
			{
				FVector StartLocationn = Block->GetActorLocation();
				FVector EndLocationn = StartLocationn + FVector(Height * 100.0f, 0.0f, 0.0f);
				FCollisionQueryParams QueryParamss;
				TArray<FHitResult> HitResultss;
				GetWorld()->LineTraceMultiByObjectType(
					HitResultss,
					StartLocationn,
					EndLocationn,
					FCollisionObjectQueryParams(ECC_WorldDynamic),
					QueryParamss

				);

			
				for (FHitResult& HitResultt : HitResultss)
				{
					if (HitResultt.GetActor() && HitResultt.GetActor()->IsA<ABlock>())
					{
						ABlock* Blockk = Cast<ABlock>(HitResultt.GetActor());
						if (Blockk && !ProcessedActors.Contains(Blockk)) // �̹� ó���� ����� ����
						{
							ProcessedActors.Add(Blockk);  // ó���� ����� �߰�
							Blockk->SetActorLocation(Blockk->GetActorLocation() + FVector(-100.0f, 0.0f, 0.0f));
						}
					}
				}


				Block->Destroy();
				
			}
		}
	}
}



