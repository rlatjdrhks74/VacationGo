/* VGUIPlayerController.h
 * Description : 해당 레벨에서 사용할 게임 모드와 UI를 띄울 플레이어 컨트롤러
 * ver 0.1 : 초기 구성 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/PlayerController.h"
#include "VGUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API AVGUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
	class UUserWidget* UIWidgetInstance;
};
