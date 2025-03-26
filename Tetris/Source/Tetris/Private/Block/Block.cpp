// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/Block.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/DataTable.h"
#include "Components/StaticMeshComponent.h"

#include "Block/BlockPiece.h"
#include "Data/MyData.h"
#include "Board/Board.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;

	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();

}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Block_Setup

void ABlock::InitBlock()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	if (nullptr != PlayerController)
	{
		AActor* CurrentCamera = PlayerController->GetViewTarget();
		PlayerController->Possess(this);
		PlayerController->SetViewTargetWithBlend(CurrentCamera, 0.0f);
	}

	for (int32 i = 0; i < 4; i++)
	{
		if (nullptr != BlockClass)
		{
			ABlockPiece* NewBlockPiece = GetWorld()->SpawnActor<ABlockPiece>(BlockPieceClass);

			if (nullptr != NewBlockPiece)
			{
				NewBlockPiece->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
				NewBlockPiece->SetActorRelativeLocation(FVector(0, 0, 0));
				BlockPieceArray.Add(NewBlockPiece);
			}
		}
	}

	const float BlockSize = UTetrisConst::BlockSize;

	// 맵의 중앙을 기준으로 X, Y 범위 설정
	float StartX = 0.0f; // 맵 중앙 X = 0
	float StartY = 0.0f; // 맵 중앙 Y = 0

	// 중앙 상단의 블록이 시작할 위치는 (5, 19)
	int StartXIndex = Board->BoardHeight - 1; // 5번째 칸에서 시작
	int StartYIndex = Board->BoardWidth - 1; // 19번째 칸

	FVector BlockStartLocation = FVector(StartX + StartXIndex * BlockSize, StartY + StartYIndex * BlockSize, 0);

	SetActorLocation(BlockStartLocation);

	InitBlockPiece();
}

void ABlock::InitBlockPiece()
{
	FName BlockTypeName = TEXT("");
	switch (BlockType)
	{
	case EBlockType::Z:
		BlockTypeName = TEXT("Z");
		break;
	case EBlockType::S:
		BlockTypeName = TEXT("S");
		break;
	case EBlockType::I:
		BlockTypeName = TEXT("I");
		break;
	case EBlockType::J:
		BlockTypeName = TEXT("J");
		break;
	case EBlockType::O:
		BlockTypeName = TEXT("O");
		break;
	case EBlockType::T:
		BlockTypeName = TEXT("T");
		break;
	case EBlockType::L:
		BlockTypeName = TEXT("L");
		break;
	}
	GetBlockOffset(BlockTypeName);
}

void ABlock::SetBlock(const FInputActionValue& Value)
{
}


#pragma	endregion

#pragma region Block_Input

void ABlock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);

	if (nullptr != EnhancedInput)
	{
		if (nullptr != MoveUpAction)
		{
			EnhancedInput->BindAction(MoveUpAction, ETriggerEvent::Started, this, &ABlock::MoveUp);
		}
		if (nullptr != MoveDownAction)
		{
			EnhancedInput->BindAction(MoveDownAction, ETriggerEvent::Started, this, &ABlock::MoveDown);
		}
		if (nullptr != MoveLeftAction)
		{
			EnhancedInput->BindAction(MoveLeftAction, ETriggerEvent::Started, this, &ABlock::MoveLeft);
		}
		if (nullptr != MoveRightAction)
		{
			EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Started, this, &ABlock::MoveRight);
		}
		if (nullptr != RotateLeftAction)
		{
			EnhancedInput->BindAction(RotateLeftAction, ETriggerEvent::Started, this, &ABlock::RotateLeft);
		}
		if (nullptr != RandomBlockAction)
		{
			EnhancedInput->BindAction(RandomBlockAction, ETriggerEvent::Started, this, &ABlock::RandomBlock);
		}
		if (nullptr != SetAction)
		{
			EnhancedInput->BindAction(SetAction, ETriggerEvent::Started, this, &ABlock::SetBlock);
		}
	}
}

void ABlock::MoveUp(const FInputActionValue& Value)
{
	TranslateBlock(FVector(100, 0, 0));
}

void ABlock::MoveDown(const FInputActionValue& Value)
{
	TranslateBlock(FVector(-100, 0, 0));
}

void ABlock::MoveLeft(const FInputActionValue& Value)
{
	TranslateBlock(FVector(0, -100, 0));
}

void ABlock::MoveRight(const FInputActionValue& Value)
{
	TranslateBlock(FVector(0, 100, 0));
}

void ABlock::RotateLeft(const FInputActionValue& Value)
{
	RotateBlock(FRotator(0, 90, 0));
}

#pragma endregion


void ABlock::RandomBlock(const FInputActionValue& Value)
{
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	int32 RandomNumber = RandomStream.RandRange(0, 6);
	BlockType = (EBlockType)RandomNumber;

	InitBlockPiece();
}

void ABlock::GetBlockOffset(const FName& BlockTypeName)
{
	if (nullptr != BlockOffsetTable)
	{

		FBlockOffSet* BlockOffsets = BlockOffsetTable->FindRow<FBlockOffSet>(BlockTypeName, nullptr);

		if (nullptr != BlockOffsets)
		{
			BlockPieceArray[0]->SetActorRelativeLocation(BlockOffsets->Offset1 * 25.0f);
			BlockPieceArray[1]->SetActorRelativeLocation(BlockOffsets->Offset2 * 25.0f);
			BlockPieceArray[2]->SetActorRelativeLocation(BlockOffsets->Offset3 * 25.0f);
			BlockPieceArray[3]->SetActorRelativeLocation(BlockOffsets->Offset4 * 25.0f);

			BlockPlaceArray.Add(FVector(BlockOffsets->Offset1));
			BlockPlaceArray.Add(FVector(BlockOffsets->Offset2));
			BlockPlaceArray.Add(FVector(BlockOffsets->Offset3));
			BlockPlaceArray.Add(FVector(BlockOffsets->Offset4));
		}
	}
}

bool ABlock::IsAllBlocksDestroyed()
{
	return false;
}

void ABlock::TranslateBlock(const FVector& Dir)
{
	bool CanMoveAllChildren = true;

	for (int i = 0; i < BlockPlaceArray.Num(); i++)
	{
		int GridX = BlockPlaceArray[i].X + (Dir.X / 100);
		int GridY = BlockPlaceArray[i].Y + (Dir.Y / 100);

		// 범위를 벗어나거나, 이미 블록이 있는 경우 이동 불가
		if (GridX < 0 || GridX >= 10 || GridY < 0 || GridY >= 20 || Board->TetrisMap[GridX][GridY] == 1)
		{
			CanMoveAllChildren = false;
			break;
		}
	}

	if (true == CanMoveAllChildren)
	{
		FVector ParentNewLocation = GetActorLocation() + Dir;
		SetActorLocation(ParentNewLocation);
	}
}

void ABlock::RotateBlock(const FRotator& Rotation)
{

}

