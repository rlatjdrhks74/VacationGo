/* BTService_Detect.h
 * Description : NPC 반경 이내 캐릭터가 있는지 감지
 * ver 0.1 : 초기 구성 - 이 창 재
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
