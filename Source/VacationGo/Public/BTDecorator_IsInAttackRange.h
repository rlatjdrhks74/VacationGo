/* BTDecorator_IsInAttackRange.h
 * Description : NPC가 공격이 가능할 경우 공격
 * ver 0.1 : 초기 구성 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
