/* VGSaveGame.cpp
 * Description : ������ �����ϰ� �ҷ����̴� ��� ������ ���� ���̺� ����
 * ver 0.1 : ���̺� ���� ���� - �� â ��
 * ver 0.2 : ���� ���� ���� ������Ʈ - �� â ��
 */

#include "VGSaveGame.h"

UVGSaveGame::UVGSaveGame()
{
	Level = 1;
	Exp = 0;
	PlayerName = TEXT("Guest");
	SaveMap = TEXT("Gameplay");
	HighScore = 0;
	CharacterIndex = 0;
}

