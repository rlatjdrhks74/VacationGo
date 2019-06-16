/* VGGamePlayWidget.h
 * Description : UI가 공용으로 사용할 기본 클래스
 */

#pragma once

#include "VacationGo.h"
#include "Blueprint/UserWidget.h"
#include "VGGamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();

protected:
	UPROPERTY()
	class UButton* ResumeButton;

	UPROPERTY()
	class UButton* ReturnToTitleButton;
};
