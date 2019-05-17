/* VGUIPlayerController.cpp
 * Description : 해당 레벨에서 사용할 게임 모드와 UI를 띄울 플레이어 컨트롤러
 * ver 0.1 : 초기 구성 - 이 창 재
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
