/* VGSaveGame.h
 * Description : 게임을 저장하고 불러들이는 기능 구현을 위한 세이브 게임
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 Exp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString PlayerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 HighScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 CharacterIndex;
};
