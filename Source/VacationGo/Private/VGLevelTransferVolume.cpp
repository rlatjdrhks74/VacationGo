/* VGLevelTransferVolume.cpp
 * Description : ������ �̵��� ���� ����
 * ver 0.1 : transfer ���� ���� - �� â ��
 * ver 0.3 : ���� ���� �̻�ÿ� ������ �̵��� �� �� �ֵ��� ��� ������Ʈ - �� â ��
 */

#include "VGLevelTransferVolume.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VGPlayerState.h"

// Sets default values
AVGLevelTransferVolume::AVGLevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AVGLevelTransferVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AVGLevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	VGPlayerState = Cast<AVGPlayerState>(Pawn->GetPlayerState());
	ABCHECK(nullptr != VGPlayerState);
	if (VGPlayerState->GetCharacterLevel() >= ToggleHidden)
	{
		ABLOG(Warning, TEXT("Current Level : %d, Require Level : %d"), VGPlayerState->GetCharacterLevel(), ToggleHidden);
		UGameplayStatics::OpenLevel(this, TransferLevelName);
	}
	else
	{
		ABLOG(Warning, TEXT("Current Level : %d, Require Level : %d"), VGPlayerState->GetCharacterLevel(), ToggleHidden);
	}
}