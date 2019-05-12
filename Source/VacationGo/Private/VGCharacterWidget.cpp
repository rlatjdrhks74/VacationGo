/* VGCharacterWidget.cpp
 * Description : ĳ���� ���� ������Ʈ�� �����Ͽ� ������ ��ȭ�� ������ ���� ������ ������Ʈ
 * ver 0.1 : ���� �ʱ� ���� - �� â ��
 * ver 0.2 : HP ���� ���� �ÿ� ���� ������Ʈ ���� - �� â ��
 */

#include "VGCharacterWidget.h"
#include "VGCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UVGCharacterWidget::BindCharacterStat(UVGCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UVGCharacterWidget::UpdateHPWidget);
}

void UVGCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UVGCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
