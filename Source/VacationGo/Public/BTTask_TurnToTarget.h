/* BTTask_TurnToTarget.h
 * Description : 공격하면서 동시에 플레이어를 향해 회전
 * ver 0.1 : 초기 구성 - 이 창 재
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
