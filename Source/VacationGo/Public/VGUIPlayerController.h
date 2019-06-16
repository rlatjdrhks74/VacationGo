/* VGUIPlayerController.h
 * Description : �ش� �������� ����� ���� ���� UI�� ��� �÷��̾� ��Ʈ�ѷ�
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
