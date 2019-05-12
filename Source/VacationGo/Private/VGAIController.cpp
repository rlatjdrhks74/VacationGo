/* VGAIController.h
 * Description : NPC 구현을 위한 AI 컨트롤러
 * ver 0.1 : AI 컨트롤러 초기 구성 - 이 창 재
 * ver 0.2 : 비헤이비어 트리 시스템으로 재구성 - 이 창 재
 * ver 0.21 : 플레이어가 반경 내에 있는지 탐지를 위한 타겟 키 생성 - 이 창 재
 */

#include "VGAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

// 기본 위치
const FName AVGAIController::HomePosKey(TEXT("HomePos"));
// 순찰할 위치
const FName AVGAIController::PatrolPosKey(TEXT("PatrolPos"));
// 타겟
const FName AVGAIController::TargetKey(TEXT("Target"));

AVGAIController::AVGAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Book/AI/BB_VGCharacter.BB_VGCharacter"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Book/AI/BT_VGCharacter.BT_VGCharacter"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AVGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}
