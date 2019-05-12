/* VGCharacterWidget.cpp
 * Description : 캐릭터 스텟 컴포넌트와 연동하여 스텟이 변화할 때마다 위젯 내용을 업데이트
 * ver 0.1 : 위젯 초기 구성 - 이 창 재
 * ver 0.2 : HP 비율 변경 시에 위젯 업데이트 구현 - 이 창 재
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
