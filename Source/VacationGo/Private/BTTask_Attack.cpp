/* BTTask_Attack.cpp
 * Description : 공격 태스크
 * ver 0.1 : 초기 구성 - 이 창 재
 */

#include "BTTask_Attack.h"
#include "VGAIController.h"
#include "VGCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto VGCharacter = Cast<AVGCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == VGCharacter)
		return EBTNodeResult::Failed;

	VGCharacter->Attack();
	IsAttacking = true;
	VGCharacter->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

