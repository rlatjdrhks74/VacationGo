/* VGAIController.h
 * Description : NPC ������ ���� AI ��Ʈ�ѷ�
 * ver 0.1 : AI ��Ʈ�ѷ� �ʱ� ���� - �� â ��
 * ver 0.2 : �����̺�� Ʈ�� �ý������� �籸�� - �� â ��
 * ver 0.21 : �÷��̾ �ݰ� ���� �ִ��� Ž���� ���� Ÿ�� Ű ���� - �� â ��
 * ver 0.23 : ������Ʈ�� �°� �����̺�� Ʈ�� ������ �������� �����ϰ� ������ �� �ְ� AI��Ʈ�ѷ� ���� ����
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
