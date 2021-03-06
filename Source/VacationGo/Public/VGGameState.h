/* VGGameState.h
 * Description : 게임의 데이터를 관리하는 게임 스테이트
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/GameStateBase.h"
#include "VGGameState.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AVGGameState();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;
};
