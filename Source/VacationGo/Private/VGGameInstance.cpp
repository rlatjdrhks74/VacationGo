/* VGGameInstance.cpp
 * Description : ĳ���� ������ �����ϱ� ���� ���� �ν��Ͻ�
 * ver 0.1 : ���� �ν��Ͻ� �ʱ� ���� - �� â ��
 */

#include "VGGameInstance.h"

UVGGameInstance::UVGGameInstance()
{
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

FVGCharacterData* UVGGameInstance::GetVGCharacterData(int32 Level)
{
	return VGCharacterTable->FindRow<FVGCharacterData>(*FString::FromInt(Level), TEXT(""));
}