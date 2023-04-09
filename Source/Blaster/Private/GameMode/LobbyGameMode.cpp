// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

ALobbyGameMode::ALobbyGameMode()
{
	NumberOfPlayersToStart = 2;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	if (NumberOfPlayers == NumberOfPlayersToStart)
	{
		UWorld* World = GetWorld();

		if (World != nullptr)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel("/Game/Maps/BlasterMap?listen");
		}
	}
}
