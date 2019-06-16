/* VGCharacterWidget.h
 * Description : 캐릭터 스텟 컴포넌트와 연동하여 스텟이 변화할 때마다 위젯 내용을 업데이트
 */

#pragma once

#include "VacationGo.h"
#include "Blueprint/UserWidget.h"
#include "VGCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UVGCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UVGCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

};
