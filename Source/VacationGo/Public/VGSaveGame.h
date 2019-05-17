/* VGSaveGame.h
 * Description : 게임을 저장하고 불러들이는 기능 구현을 위한 세이브 게임
 * ver 0.1 : 세이브 게임 구성 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/SaveGame.h"
#include "VGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UVGSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;

	UPROPERTY()
	int32 CharacterIndex;
};
