/* VGGameState.cpp
 * Description : ������ �����͸� �����ϴ� ���� ������Ʈ
 * ver 0.1 : ���� ������Ʈ �ʱ� ���� - �� â ��
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