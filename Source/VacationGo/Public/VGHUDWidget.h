/* VGHUBWidget.h
 * Description : ���� �⺻ UI ������ ���� ��� ����
 */

#pragma once

#include "VacationGo.h"
#include "Blueprint/UserWidget.h"
#include "VGHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UVGCharacterStatComponent* CharacterStat);
	void BindPlayerState(class AVGPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class UVGCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class AVGPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* MapName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;
};
