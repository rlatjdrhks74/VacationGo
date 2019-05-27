/* VGGameMode.h
 * Description : 게임의 규칙을 관리하는 게임모드
 * ver 0.1 : 게임모드 구성 - 이 창 재
 */

#include "VGGameMode.h"
#include "VGPlayerController.h"
#include "VGCharacter.h"
#include "VGPlayerState.h"
#include "VGGameState.h"

AVGGameMode::AVGGameMode()
{
	// 각각의 클래스 속성 값을 해당 클래스 값으로 변경
	DefaultPawnClass = LoadObject<UClass>(AVGCharacter::StaticClass(), TEXT("/Game/Book/Blueprints/BP_VGCharacter.BP_VGCharacter_C"));
	PlayerControllerClass = AVGPlayerController::StaticClass();
	PlayerStateClass = AVGPlayerState::StaticClass();
	GameStateClass = AVGGameState::StaticClass();
	//ScoreToClear = 2;
}

void AVGGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	VGGameState = Cast<AVGGameState>(GameState);
}

void AVGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto VGPlayerState = Cast<AVGPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != VGPlayerState);
	VGPlayerState->InitPlayerData();
}

void AVGGameMode::AddScore(AVGPlayerController * ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto VGPlayerController = Cast<AVGPlayerController>(It->Get());
		if ((nullptr != VGPlayerController) && (ScoredPlayer == VGPlayerController))
		{
			VGPlayerController->AddGameScore();
			break;
		}
	}

	VGGameState->AddGameScore();

	//if (GetScore() >= ScoreToClear)
	//{
	//	VGGameState->SetGameCleared();

	//	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	//	{
	//		(*It)->TurnOff();
	//	}

	//	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	//	{
	//		const auto VGPlayerController = Cast<AVGPlayerController>(It->Get());
	//		if (nullptr != VGPlayerController)
	//		{
	//			VGPlayerController->ShowResultUI();
	//		}
	//	}
	//}
}
//
//int32 AVGGameMode::GetScore() const
//{
//	return VGGameState->GetTotalGameScore();
//}
//
//
