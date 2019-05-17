/* VGUIPlayerController.cpp
 * Description : �ش� �������� ����� ���� ���� UI�� ��� �÷��̾� ��Ʈ�ѷ�
 * ver 0.1 : �ʱ� ���� - �� â ��
 */

#include "VGUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void AVGUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABCHECK(nullptr != UIWidgetClass);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	ABCHECK(nullptr != UIWidgetInstance);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
