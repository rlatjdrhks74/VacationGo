/* BTTask_TurnToTarget.cpp
 * Description : 공격하면서 동시에 플레이어를 향해 회전을 위한 별도의 비헤이비어 트리 코드
 * ver 0.1 : 초기 구성 - 이 창 재
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
