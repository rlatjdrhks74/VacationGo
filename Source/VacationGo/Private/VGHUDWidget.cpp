/* VGHUBWidget.cpp
 * Description : 게임 기본 UI 관리를 위한 허브 위젯
 * ver 0.1 : 허브 위젯 구성 - 이 창 재
 * ver 0.5 : 맵 이름 지정 및 UI 보강 - 이 창 재
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

	MapName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMap")));

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

	if (GetWorld()->GetMapName().Equals("UEDPIE_0_Cave") || GetWorld()->GetMapName().Equals("UEDPIE_0_CaveB"))
	{
		MapName->SetText(FText::FromString("Cave"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Gameplay") || GetWorld()->GetMapName().Equals("UEDPIE_0_GameplayB") || GetWorld()->GetMapName().Equals("UEDPIE_0_GameplayC") || GetWorld()->GetMapName().Equals("UEDPIE_0_GameplayD"))
	{
		MapName->SetText(FText::FromString("River Mountain"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Inside1") || GetWorld()->GetMapName().Equals("UEDPIE_0_Inside1B"))
	{
		MapName->SetText(FText::FromString("Castle Inside"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Inside2") || GetWorld()->GetMapName().Equals("UEDPIE_0_Inside2B") || GetWorld()->GetMapName().Equals("UEDPIE_0_Inside2C"))
	{
		MapName->SetText(FText::FromString("Castle Stairs"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Outside"))
	{
		MapName->SetText(FText::FromString("Town"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Outside2"))
	{
		MapName->SetText(FText::FromString("Wretched Automatons"));
	}
	else if (GetWorld()->GetMapName().Equals("UEDPIE_0_Ocean"))
	{
		MapName->SetText(FText::FromString("Ocean Paradise"));
	}
	else
	{
		MapName->SetText(FText::FromString(GetWorld()->GetMapName()));
	}

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
}