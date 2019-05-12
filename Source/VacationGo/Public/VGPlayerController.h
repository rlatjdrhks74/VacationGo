/* VGPlayerController.h
 * Description : 플레이어를 대변하여 폰을 조종하는 컨트롤러
 * ver 0.1 : 플레이어 컨트롤러 초기 구성 - 이 창 재
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
