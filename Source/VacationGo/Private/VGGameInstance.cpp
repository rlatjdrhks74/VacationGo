/* VGGameInstance.cpp
 * Description : 캐릭터 스텟을 관리하기 위한 게임 인스턴스
 * ver 0.1 : 게임 인스턴스 초기 구성 - 이 창 재
 */

#include "VGGameInstance.h"

UVGGameInstance::UVGGameInstance()
{
	// 별도로 만들어 둔 캐릭터 스텟 데이터를 가져온다.
	FString CharacterDataPath = TEXT("/Game/Book/GameData/VGCharacterData.VGCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_VGCHARACTER(*CharacterDataPath);
	ABCHECK(DT_VGCHARACTER.Succeeded());
	VGCharacterTable = DT_VGCHARACTER.Object;
	ABCHECK(VGCharacterTable->GetRowMap().Num() > 0);
}

void UVGGameInstance::Init()
{
	Super::Init();
}

// 레벨에 따른 케릭터 스텟 데이터 탐색
FVGCharacterData* UVGGameInstance::GetVGCharacterData(int32 Level)
{
	return VGCharacterTable->FindRow<FVGCharacterData>(*FString::FromInt(Level), TEXT(""));
}