/* VGPlayerController.cpp
 * Description : 플레이어를 대변하여 폰을 조종하는 컨트롤러
 * ver 0.1 : 플레이어 컨트롤러 초기 구성 - 이 창 재
 */

#include "VGPlayerController.h"

void AVGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// 폰에 빙의를 진행하는 시점 파악
void AVGPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AVGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
