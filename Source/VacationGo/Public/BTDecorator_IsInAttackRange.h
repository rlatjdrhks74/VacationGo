/* BTDecorator_IsInAttackRange.h
 * Description : NPC�� ������ ������ ��� ����
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
