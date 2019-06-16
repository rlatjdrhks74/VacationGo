/* VGAIController.h
 * Description : NPC ������ ���� AI ��Ʈ�ѷ�
 */

#pragma once

#include "VacationGo.h"
#include "AIController.h"
#include "VGAIController.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AVGAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
