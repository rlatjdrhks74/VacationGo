/* BTTask_TurnToTarget.cpp
 * Description : �����ϸ鼭 ���ÿ� �÷��̾ ���� ȸ���� ���� ������ �����̺�� Ʈ�� �ڵ�
 * ver 0.1 : �ʱ� ���� - �� â ��
 */


#include "BTTask_TurnToTarget.h"
#include "VGAIController.h"
#include "VGCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto VGCharacter = Cast<AVGCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == VGCharacter)
		return EBTNodeResult::Failed;

	auto Target = Cast<AVGCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AVGAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - VGCharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	VGCharacter->SetActorRotation(FMath::RInterpTo(VGCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
