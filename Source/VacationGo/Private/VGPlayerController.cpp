/* VGPlayerController.cpp
 * Description : �÷��̾ �뺯�Ͽ� ���� �����ϴ� ��Ʈ�ѷ�
 * ver 0.1 : �÷��̾� ��Ʈ�ѷ� �ʱ� ���� - �� â ��
 */

#include "VGPlayerController.h"

void AVGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// ���� ���Ǹ� �����ϴ� ���� �ľ�
void AVGPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AVGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
