/* VGSaveGame.cpp
 * Description : 게임을 저장하고 불러들이는 기능 구현을 위한 세이브 게임
 * ver 0.1 : 세이브 게임 구성 - 이 창 재
 */

#include "VGSaveGame.h"

UVGSaveGame::UVGSaveGame()
{
	Level = 1;
	Exp = 0;
	PlayerName = TEXT("Guest");
	HighScore = 0;
	CharacterIndex = 0;
}

