/* VGPlayerState.cpp
 * Description : 플레이어의 정보를 관리하기 위한 플레이어 스테이트
 * ver 0.1 : PlayerState 구성 - 이 창 재
 */

#include "VGPlayerState.h"
#include "VGGameInstance.h"
#include "VGSaveGame.h"

AVGPlayerState::AVGPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");
	CharacterIndex = 0;
}


int32 AVGPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 AVGPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 AVGPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 AVGPlayerState::GetCharacterIndex() const
{
	return CharacterIndex;
}

void AVGPlayerState::InitPlayerData()
{
	auto VGSaveGame = Cast<UVGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == VGSaveGame)
	{
		VGSaveGame = GetMutableDefault<UVGSaveGame>();
	}

	SetPlayerName(VGSaveGame->PlayerName);
	SetCharacterLevel(VGSaveGame->Level);
	GameScore = 0;
	GameHighScore = VGSaveGame->HighScore;
	Exp = VGSaveGame->Exp;
	CharacterIndex = VGSaveGame->CharacterIndex;
	SavePlayerData();
}

void AVGPlayerState::SavePlayerData()
{
	UVGSaveGame* NewPlayerData = NewObject<UVGSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}

float AVGPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool AVGPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
	return DidLevelUp;
}

void AVGPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void AVGPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto VGGameInstance = Cast<UVGGameInstance>(GetGameInstance());
	ABCHECK(nullptr != VGGameInstance);

	CurrentStatData = VGGameInstance->GetVGCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}
