/* VGHUBWidget.cpp
 * Description : 게임 기본 UI 관리를 위한 허브 위젯
 * ver 0.1 : 허브 위젯 구성 - 이 창 재
 */


#include "VGHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "VGCharacterStatComponent.h"
#include "VGPlayerState.h"

void UVGHUDWidget::BindCharacterStat(UVGCharacterStatComponent* CharacterStat)
{
	ABCHECK(nullptr != CharacterStat);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UVGHUDWidget::UpdateCharacterStat);
}

void UVGHUDWidget::BindPlayerState(AVGPlayerState * PlayerState)
{
	ABCHECK(nullptr != PlayerState);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UVGHUDWidget::UpdatePlayerState);
}

void UVGHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(nullptr != HPBar);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	ABCHECK(nullptr != ExpBar);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	ABCHECK(nullptr != PlayerName);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	ABCHECK(nullptr != PlayerLevel);
}

void UVGHUDWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UVGHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
}