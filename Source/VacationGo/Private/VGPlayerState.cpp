/* VGPlayerState.cpp
 * Description : 플레이어의 정보를 관리하기 위한 플레이어 스테이트
 * ver 0.1 : PlayerState 구성 - 이 창 재
 * ver 0.2 : 현재 위치 저장을 위한 레벨 저장기능 업데이트 - 이 창 재
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

// 세이브 데이터 생성 후 초기 플레이어 데이터 삽입
void AVGPlayerState::InitPlayerData()
{
	auto VGSaveGame = Cast<UVGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == VGSaveGame)
	{
		VGSaveGame = GetMutableDefault<UVGSaveGame>();
	}

	SetPlayerName(VGSaveGame->PlayerName); // 플레이어 닉네임
	SetCharacterLevel(VGSaveGame->Level); // 캐릭터 레벨
	GameScore = 0; // 게임 스코어 -- 쓰이지 않음
	GameHighScore = VGSaveGame->HighScore; // 게임 하이스코어 -- 쓰이지 않음
	Exp = VGSaveGame->Exp; // 경험치
	CharacterIndex = VGSaveGame->CharacterIndex; // 에셋 인덱스
	SaveMap = VGSaveGame->SaveMap; // 현재 레벨(맵)
	ABLOG(Warning, TEXT("FUckingSHIT? : %s"), *SaveMap);
	SavePlayerData();
}

// 플레이어 데이터 저장 
void AVGPlayerState::SavePlayerData()
{
	UVGSaveGame* NewPlayerData = NewObject<UVGSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;
	NewPlayerData->SaveMap = GetWorld()->GetMapName().RightChop(9);
	ABLOG(Warning, TEXT("SHITFUCKING? : %s"), *NewPlayerData->SaveMap);
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

// 경험치를 더해주고 다음 레벨로 업 할수 있는지 체킹
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

// 레벨에 따른 스텟 데이터가 다르므로 레벨 업시 새로운 스텟 데이터 세팅
void AVGPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto VGGameInstance = Cast<UVGGameInstance>(GetGameInstance());
	ABCHECK(nullptr != VGGameInstance);

	CurrentStatData = VGGameInstance->GetVGCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}
