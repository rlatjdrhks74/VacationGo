// Fill out your copyright notice in the Description page of Project Settings.

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
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HighScore;
};
