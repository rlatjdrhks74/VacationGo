/* VGGameMode.h
 * Description : ������ ��Ģ�� �����ϴ� ���Ӹ��
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/GameModeBase.h"
#include "VGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AVGGameMode();
	
public:
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class AVGPlayerController *Player);
//	int32 GetScore() const;

private:
	UPROPERTY()
	class AVGGameState* VGGameState;
//
//	UPROPERTY()
//	int32 ScoreToClear;
//	
};
