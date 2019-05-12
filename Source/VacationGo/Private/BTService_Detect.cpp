/* BTService_Detect.cpp
 * Description : NPC 반경 이내 캐릭터가 있는지 감지
 * ver 0.1 : 초기 구성 - 이 창 재
 * ver 0.15 : 타겟이 반경 내에 있으면 초록색 구 생성 및 플레이어를 따라다니도록 설정 - 이 창 재
 */

#include "BTService_Detect.h"
#include "VGAIController.h"
#include "VGCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld * World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	// 반경 3미터 이내 플레이어가 있는지 탐지
	float DetectRadius = 300.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			AVGCharacter* VGCharacter = Cast<AVGCharacter>(OverlapResult.GetActor());
			if (VGCharacter && VGCharacter->GetController()->IsPlayerController())
			{
				// 기본 동작으로 플레이어를 탐지하면 플레이어를 따라다니도록 설정. 
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AVGAIController::TargetKey, VGCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, VGCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), VGCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AVGAIController::TargetKey, nullptr);
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}


