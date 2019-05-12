/* VGCharacterWidget.h
 * Description : ĳ���� ���� ������Ʈ�� �����Ͽ� ������ ��ȭ�� ������ ���� ������ ������Ʈ
 * ver 0.1 : ���� �ʱ� ���� - �� â ��
 * ver 0.2 : HP ���� ���� �ÿ� ���� ������Ʈ ���� - �� â ��
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