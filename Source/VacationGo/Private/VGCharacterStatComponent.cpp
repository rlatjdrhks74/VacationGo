/* VGCharacterStatComponent.cpp
 * Description : ĳ���� ���� ������Ʈ
 * ver 0.1 : ������Ʈ �ʱ� ���� - �� â ��
 * ver 0.1.5 : ���� �ν��Ͻ����� �����͸� ������ �ʱ�ȭ�ϰ� ������ ����Ǹ� �ش� ������ �ٲ�� �ڵ� ���� - �� â ��
 * ver 0.2 : ĳ���Ͱ� �������� ������ ��������ŭ �� HP�� �����ǰ� 0���� �۾����� �׵��� ����߰� - �� â ��
 * ver 0.25 : HP�� ������Ʈ ����
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