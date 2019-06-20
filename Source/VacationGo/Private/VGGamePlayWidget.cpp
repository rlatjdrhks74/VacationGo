/* VGGamePlayWidget.cpp
 * Description : ���� Pause UI ������ ���� Ŭ���� �ڵ�
 * ver 0.1 : ���� �÷��� ���� ���� - �� â ��
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
