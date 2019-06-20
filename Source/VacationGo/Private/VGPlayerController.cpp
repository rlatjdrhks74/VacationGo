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
#include <VGLevelTransferVolume.h>

AVGPlayerController::AVGPlayerController()
{
	// 기본 게임 UI
	static ConstructorHelpers::FClassFinder<UVGHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	// 게임 Pause시 등장하는 UI
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
	// Game Pause Input 바인딩
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

// 허브 위젯
UVGHUDWidget* AVGPlayerController::GetHUDWidgetWithCreation()
{
	return HUDWidget;
}

// NPC 킬시 경험치 업 -- 사용 보류
void AVGPlayerController::NPCKill(AVGCharacter* KilledNPC) const
{
	VGPlayerState->AddExp(KilledNPC->GetExp());
}

// 경험치 업
void AVGPlayerController::ExpUp(int32 exp) const
{
	VGPlayerState->AddExp(exp);
}

// 게임 스코어 추가 -- 사용 보류
void AVGPlayerController::AddGameScore() const
{
	VGPlayerState->AddGameScore();
}

// 게임중일때와 UI 메뉴에 있을때에 따른 Input Mode 변환 함수
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

// Game Pause 구현 함수
void AVGPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UVGGamePlayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}