/* VGPlayerController.cpp
 * Description : �÷��̾ �뺯�Ͽ� ���� �����ϴ� ��Ʈ�ѷ�
 * ver 0.1 : �÷��̾� ��Ʈ�ѷ� �ʱ� ���� - �� â ��
 * ver 0.15 : ������� ���� �ڵ� �߰� - �� â ��
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

// ���� ���Ǹ� �����ϴ� ���� �ľ�
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
	
	// ���� ������Ʈ ������ HUB�� ����
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