/* BTService_Detect.h
 * Description : NPC �ݰ� �̳� ĳ���Ͱ� �ִ��� ����
 * ver 0.1 : �ʱ� ���� - �� â ��
 */

#pragma once

#include "VacationGo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
