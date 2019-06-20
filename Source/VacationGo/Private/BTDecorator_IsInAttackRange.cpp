/* BTDecorator_IsInAttackRange.cpp
 * Description : NPC가 공격이 가능할 경우 공격을 위한 비헤이비어 트리 코드
 * ver 0.1 : 초기 구성 - 이 창 재
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

