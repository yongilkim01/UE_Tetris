// Fill out your copyright notice in the Description page of Project Settings.


#include "Blocks.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Block.h"

#include "Engine/DataTable.h"

#include "Components/StaticMeshComponent.h"

#include "MyDataAsset.h"

// Sets default values
ABlocks::ABlocks()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();
}

// Called when the game starts or when spawned
void ABlocks::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		AActor* CurrentCamera = PlayerController->GetViewTarget();
		PlayerController->Possess(this);
		PlayerController->SetViewTargetWithBlend(CurrentCamera, 0.0f);
	}
	for (int32 i = 0; i < 4; i++)
	{
		if (BlockClass)
		{
			ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(BlockClass);
			if (NewBlock)
			{
				NewBlock->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
				NewBlock->SetActorRelativeLocation(FVector(0, 0, 0));
				BlockArray.Add(NewBlock);
			}
		}
	}
	RandomBlock(FInputActionValue());
}

// Called every frame
void ABlocks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAllBlocksDestroyed())
	{
		Destroy();
	}

}

// Called to bind functionality to input
void ABlocks::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
	if (EnhancedInput != nullptr)
	{
		if (nullptr != MoveUpAction)
		{
			EnhancedInput->BindAction(MoveUpAction, ETriggerEvent::Started, this, &ABlocks::MoveUp);
		}
		if (nullptr != MoveDownAction)
		{
			EnhancedInput->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &ABlocks::MoveDown);
		}
	

		if (nullptr != MoveLeftAction)
		{
			EnhancedInput->BindAction(MoveLeftAction, ETriggerEvent::Started, this, &ABlocks::MoveLeft);
		}
		if (nullptr != MoveRightAction)
		{
			EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Started, this, &ABlocks::MoveRight);
		}
		if (nullptr != RotateLeftAction)
		{
			EnhancedInput->BindAction(RotateLeftAction, ETriggerEvent::Started, this, &ABlocks::RotateLeft);
		}
		if (nullptr != RandomBlockAction)
		{
			EnhancedInput->BindAction(RandomBlockAction, ETriggerEvent::Started, this, &ABlocks::RandomBlock);
		}
		if (nullptr != SetAction)
		{
			EnhancedInput->BindAction(SetAction, ETriggerEvent::Started, this, &ABlocks::SetBlock);
		}
		if (nullptr != GameEndAction)
		{
			EnhancedInput->BindActionValueLambda(GameEndAction, ETriggerEvent::Started, [this](const FInputActionValue& Value) 
				{
					APlayerController* PlayerController = Cast<APlayerController>(GetController());
					if (PlayerController)
					{
						PlayerController->ConsoleCommand(TEXT("quit"));
					}
				});
		}
	}
}

void ABlocks::MoveUp(const FInputActionValue& Value)
{
	CheckMoveable(FVector(100, 0, 0));
}

void ABlocks::MoveDown(const FInputActionValue& Value)
{
	CheckMoveable(FVector(-100, 0, 0));
}

void ABlocks::MoveLeft(const FInputActionValue& Value)
{
	CheckMoveable(FVector(0, -100, 0));
}

void ABlocks::MoveRight(const FInputActionValue& Value)
{
	CheckMoveable(FVector(0, 100, 0));
}

void ABlocks::RotateLeft(const FInputActionValue& Value)
{
	CheckRotateable(FRotator(0, 90, 0));
}

void ABlocks::RandomBlock(const FInputActionValue& Value)
{
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	int32 RandomNumber = RandomStream.RandRange(0, 6);
	BlockType = (EBlockType)RandomNumber;
	InitBlock();
}

void ABlocks::InitBlock()
{

	SetActorLocation(FVector(MapSize->Height*100.0f*0.5f, 0, 0));
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

void ABlocks::GetBlockOffset(const FName& BlockTypeName)
{
	if (BlockOffsetTable)
	{

		FBlockOffSet* BlockOffsets = BlockOffsetTable->FindRow<FBlockOffSet>(BlockTypeName, nullptr);


		if (BlockOffsets)
		{
			BlockArray[0]->SetActorRelativeLocation(BlockOffsets->Offset1);
			BlockArray[1]->SetActorRelativeLocation(BlockOffsets->Offset2);
			BlockArray[2]->SetActorRelativeLocation(BlockOffsets->Offset3);
			BlockArray[3]->SetActorRelativeLocation(BlockOffsets->Offset4);
		}
	}
}

bool ABlocks::IsAllBlocksDestroyed()
{
	for (ABlock* Block : BlockArray)
	{
		if (IsValid(Block)) // 블록이 아직 살아있으면 false
		{
			return false;
		}
	}
	return true; // 모든 블록이 삭제됨
}

void ABlocks::SetBlock(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AActor* CurrentCamera = PlayerController->GetViewTarget();
		PlayerController->UnPossess();
		PlayerController->SetViewTargetWithBlend(CurrentCamera, 0.0f);
	}
	for (ABlock* Block : BlockArray)
	{
		if (Block)
		{
			Block->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UStaticMeshComponent* MeshComp = Block->FindComponentByClass<UStaticMeshComponent>();
			if (MeshComp)
			{
				MeshComp->SetCollisionProfileName(TEXT("BlockAll"));
				MeshComp->BodyInstance.SetObjectType(ECollisionChannel::ECC_WorldDynamic);
				
			}
		}
	}

	if (BlockClass)
	{
		ABlocks* NewBlock = GetWorld()->SpawnActor<ABlocks>(BlocksClass);
	}
}

void ABlocks::CheckMoveable(const FVector& Dir)
{
	bool CanMoveAllChildren = true;

	for (ABlock* Block : BlockArray)
	{
		if (Block)
		{
			FVector StartLocation = Block->GetActorLocation();
			FVector EndLocation = StartLocation + Dir;

			FCollisionQueryParams QueryParams;
			FHitResult HitResult;
			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				StartLocation,
				EndLocation,
				ECC_Visibility,
				QueryParams
			);

		

			if (bHit) // 충돌한 경우만 처리
			{

				CanMoveAllChildren = false;
				break;


			}
		}
	}

	if (CanMoveAllChildren)
	{
		FVector ParentNewLocation = GetActorLocation() + Dir;
		SetActorLocation(ParentNewLocation);
	}
}

void ABlocks::CheckRotateable(const FRotator& Rotation)
{
	bool CanRotateAllChildren = true;

	FVector ParentLocation = GetActorLocation();

	for (ABlock* Block : BlockArray)
	{
		if (Block)
		{
			FVector RelativeLocation = Block->GetActorLocation() - ParentLocation;
			FVector RotatedLocation = Rotation.RotateVector(RelativeLocation) + ParentLocation;

			FCollisionQueryParams QueryParams;
	
			FHitResult HitResult;
			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Block->GetActorLocation(),
				RotatedLocation,
				ECC_Visibility,
				QueryParams
			);
			if (bHit) // 충돌 발생
			{
				CanRotateAllChildren = false;
				break;
			}
		}
	}

	if (CanRotateAllChildren)
	{
		SetActorRotation(GetActorRotation() + Rotation);
	}
}





