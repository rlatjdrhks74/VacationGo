/* BTDecorator_IsInAttackRange.cpp
 * Description : NPC�� ������ ������ ��� ������ ���� �����̺�� Ʈ�� �ڵ�
 * ver 0.1 : �ʱ� ���� - �� â ��
 */

#include "BTDecorator_IsInAttackRange.h"
#include "VGAIController.h"
#include "VGCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = Cast<AVGCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<AVGCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AVGAIController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= ControllingPawn->GetFinalAttackRange());
	return bResult;
}

