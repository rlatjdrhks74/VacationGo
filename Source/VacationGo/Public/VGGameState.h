/* VGGameState.h
 * Description : ������ �����͸� �����ϴ� ���� ������Ʈ
 * ver 0.1 : ���� ������Ʈ �ʱ� ���� - �� â ��
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
