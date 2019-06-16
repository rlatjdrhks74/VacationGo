/* VGPlayerController.h
 * Description : 플레이어를 대변하여 폰을 조종하는 컨트롤러
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
	AVGPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	class UVGHUDWidget* GetHUDWidgetWithCreation();
	void NPCKill(class AVGCharacter* KilledNPC) const;
	void ExpUp(int32 exp) const;
	void AddGameScore() const;
	void ChangeInputMode(bool bGameMode = true);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UVGHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UVGGamePlayWidget> MenuWidgetClass;

private:
	void OnGamePause();

	UPROPERTY()
	class UVGHUDWidget* HUDWidget;

	UPROPERTY()
	class AVGPlayerState* VGPlayerState;

	UPROPERTY()
	class AVGLevelTransferVolume* VGLevelTransferVolume;

	UPROPERTY()
	class UVGGamePlayWidget* MenuWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

};
