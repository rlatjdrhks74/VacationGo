/* VGSaveGame.h
 * Description : ������ �����ϰ� �ҷ����̴� ��� ������ ���� ���̺� ����
 * ver 0.1 : ���̺� ���� ���� - �� â ��
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
