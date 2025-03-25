// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/MainCameraActor.h"

void AMainCameraActor::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->SetViewTargetWithBlend(this);
    }
}
