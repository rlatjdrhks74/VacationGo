/* VGPlayerController.cpp
 * Description : 플레이어를 대변하여 폰을 조종하는 컨트롤러
 * ver 0.1 : 플레이어 컨트롤러 초기 구성 - 이 창 재
 * ver 0.15 : 허브위젯 지원 코드 추가 - 이 창 재
 */

#include "VGPlayerController.h"
#include "VGHUDWidget.h"
#include "VGPlayerState.h"
#include "VGCharacter.h"
#include "VGGamePlayWidget.h"

AVGPlayerController::AVGPlayerController()
{
	static ConstructorHelpers::FClassFinder<UVGHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UVGGamePlayWidget> UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}
}

void AVGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// 폰에 빙의를 진행하는 시점 파악
void AVGPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AVGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AVGPlayerController::OnGamePause);
}

void AVGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UVGHUDWidget>(this, HUDWidgetClass);
	ABCHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport(1);
	
	// 스텟 컴포넌트 정보를 HUB에 연동
	VGPlayerState = Cast<AVGPlayerState>(PlayerState);
	ABCHECK(nullptr != VGPlayerState);
	HUDWidget->BindPlayerState(VGPlayerState);
	VGPlayerState->OnPlayerStateChanged.Broadcast();
}

UVGHUDWidget* AVGPlayerController::GetHUDWidgetWithCreation()
{
	return HUDWidget;
}

void AVGPlayerController::NPCKill(AVGCharacter* KilledNPC) const
{
	VGPlayerState->AddExp(KilledNPC->GetExp());
}

void AVGPlayerController::AddGameScore() const
{
	VGPlayerState->AddGameScore();
}

void AVGPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void AVGPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UVGGamePlayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}