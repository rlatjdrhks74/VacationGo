/* VGPlayerState.h
 * Description : 플레이어의 정보를 관리하기 위한 플레이어 스테이트
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/PlayerState.h"
#include "VGPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AVGPlayerState();

	int32 GetGameScore() const;
	int32 GetGameHighScore() const;
	FString SaveSlotName;
	
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetCharacterLevel() const;

	int32 GetCharacterIndex() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 GameHighScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

	UPROPERTY(Transient)
	int32 CharacterIndex;

	UPROPERTY(Transient)
	FString SaveMap;
private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FVGCharacterData* CurrentStatData;
};
