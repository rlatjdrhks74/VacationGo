/* VGPlayerController.h
 * Description : �÷��̾ �뺯�Ͽ� ���� �����ϴ� ��Ʈ�ѷ�
 * ver 0.1 : �÷��̾� ��Ʈ�ѷ� �ʱ� ���� - �� â ��
 */
#pragma once

#include "VacationGo.h"
#include "GameFramework/PlayerController.h"
#include "VGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
};
