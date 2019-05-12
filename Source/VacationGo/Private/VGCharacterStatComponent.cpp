/* VGCharacterStatComponent.cpp
 * Description : 캐릭터 스텟 컴포넌트
 * ver 0.1 : 컴포넌트 초기 구성 - 이 창 재
 * ver 0.1.5 : 게임 인스턴스에서 데이터를 가져와 초기화하고 레벨이 변경되면 해당 스탯이 바뀌도록 코드 수정 - 이 창 재
 * ver 0.2 : 캐릭터가 데미지를 받으면 데미지만큼 현 HP가 차감되고 0보다 작아지면 죽도록 기능추가 - 이 창 재
 * ver 0.25 : HP바 업데이트 구현
 */

#include "VGCharacterStatComponent.h"
#include "VGGameInstance.h"

// Sets default values for this component's properties
UVGCharacterStatComponent::UVGCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UVGCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UVGCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UVGCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto VGGameInstance = Cast<UVGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != VGGameInstance);
	CurrentStatData = VGGameInstance->GetVGCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UVGCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void UVGCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UVGCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

float UVGCharacterStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}