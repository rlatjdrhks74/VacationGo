/* VGGameState.cpp
 * Description : 게임의 데이터를 관리하는 게임 스테이트
 * ver 0.1 : 게임 스테이트 초기 구성 - 이 창 재
 */

#include "VGGameState.h"

AVGGameState::AVGGameState()
{
	TotalGameScore = 0;
}

int32 AVGGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void AVGGameState::AddGameScore()
{
	TotalGameScore++;
}