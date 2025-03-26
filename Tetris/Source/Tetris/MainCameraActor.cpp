// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraActor.h"
#include "MyDataAsset.h"

void AMainCameraActor::BeginPlay()
{
	Super::BeginPlay();
	float Size = (MapSize->Width > MapSize->Height) ? MapSize->Width : MapSize->Height;
    SetActorLocation(FVector(0, 0, Size*120.0f));
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->SetViewTargetWithBlend(this); 
    }
}
