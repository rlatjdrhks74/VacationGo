/* BTTask_TurnToTarget.h
 * Description : �����ϸ鼭 ���ÿ� �÷��̾ ���� ȸ��
 * ver 0.1 : �ʱ� ���� - �� â ��
 */

#pragma once

#include "VacationGo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
