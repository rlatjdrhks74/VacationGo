/* VGCharacterSelectWidget.cpp
 * Description : 캐릭터 선택화면 UI 구성을 위한 위젯
 * ver 0.1 : 초기 구성 - 이 창 재
 */

#include "VGCharacterSelectWidget.h"
#include "VGCharacterSetting.h"
#include "VGGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "VGSaveGame.h"
#include "VGPlayerState.h"

void UVGCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1) CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex) CurrentIndex = 0;

	auto CharacterSetting = GetDefault<UVGCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto VGGameInstance = GetWorld()->GetGameInstance<UVGGameInstance>();
	ABCHECK(nullptr != VGGameInstance);
	ABCHECK(TargetComponent.IsValid());

	USkeletalMesh * Asset = VGGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (nullptr != Asset)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}

void UVGCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<UVGCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	ABCHECK(nullptr != PrevButton);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	ABCHECK(nullptr != NextButton);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	ABCHECK(nullptr != TextBox);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	ABCHECK(nullptr != ConfirmButton);

	PrevButton->OnClicked.AddDynamic(this, &UVGCharacterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &UVGCharacterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &UVGCharacterSelectWidget::OnConfirmClicked);
}

void UVGCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void UVGCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void UVGCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10) return;

	UVGSaveGame * NewPlayerData = NewObject<UVGSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto VGPlayerState = GetDefault<AVGPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, VGPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("GamePlay"));
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}

