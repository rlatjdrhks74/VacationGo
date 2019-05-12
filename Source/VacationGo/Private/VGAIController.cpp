/* VGAIController.h
 * Description : NPC ������ ���� AI ��Ʈ�ѷ�
 * ver 0.1 : AI ��Ʈ�ѷ� �ʱ� ���� - �� â ��
 * ver 0.2 : �����̺�� Ʈ�� �ý������� �籸�� - �� â ��
 * ver 0.21 : �÷��̾ �ݰ� ���� �ִ��� Ž���� ���� Ÿ�� Ű ���� - �� â ��
 */

#include "VGAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

// �⺻ ��ġ
const FName AVGAIController::HomePosKey(TEXT("HomePos"));
// ������ ��ġ
const FName AVGAIController::PatrolPosKey(TEXT("PatrolPos"));
// Ÿ��
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
