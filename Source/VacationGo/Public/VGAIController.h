/* VGAIController.h
 * Description : NPC 구현을 위한 AI 컨트롤러
 * ver 0.1 : AI 컨트롤러 초기 구성 - 이 창 재
 * ver 0.2 : 비헤이비어 트리 시스템으로 재구성 - 이 창 재
 * ver 0.21 : 플레이어가 반경 내에 있는지 탐지를 위한 타겟 키 생성 - 이 창 재
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

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
