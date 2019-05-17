/* VGPlayerState.h
 * Description : 플레이어의 정보를 관리하기 위한 플레이어 스테이트
 * ver 0.1 : PlayerState 구성 - 이 창 재
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
private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FVGCharacterData* CurrentStatData;
};
