// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/MainCameraActor.h"
#include "Data/MyDataAsset.h"

void AMainCameraActor::BeginPlay()
{
    Super::BeginPlay();
    float Size = (MapSize->Width > MapSize->Height) ? MapSize->Width : MapSize->Height;
    SetActorLocation(FVector(0, 0, Size * 60.0f));
	AddActorWorldRotation(FRotator(0, 90.0f, 0));
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->SetViewTargetWithBlend(this);
    }
}
