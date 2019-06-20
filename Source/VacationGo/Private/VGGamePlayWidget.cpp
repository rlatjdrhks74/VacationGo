/* VGGamePlayWidget.cpp
 * Description : 게임 Pause UI 구현을 위한 클래스 코드
 * ver 0.1 : 게임 플레이 위젯 구성 - 이 창 재
 */

#include "VGGamePlayWidget.h"
#include "Components/Button.h"
#include "VGPlayerController.h"

void UVGGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UVGGamePlayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UVGGamePlayWidget::OnReturnToTitleClicked);
	}
}

void UVGGamePlayWidget::OnResumeClicked()
{
	auto VGPlayerController = Cast<AVGPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != VGPlayerController);

	RemoveFromParent();
	VGPlayerController->ChangeInputMode(true);
	VGPlayerController->SetPause(false);
}

void UVGGamePlayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}
