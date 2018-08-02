// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode.h"
#include "BPlayerController.h"

ABGameMode::ABGameMode()
{
	PlayerControllerClass = ABPlayerController::StaticClass();
}


