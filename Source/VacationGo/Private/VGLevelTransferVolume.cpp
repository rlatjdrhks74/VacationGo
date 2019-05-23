/* VGLevelTransferVolume.cpp
 * Description : 레벨간 이동을 위한 볼륨
 * ver 0.1 : transfer 볼륨 구성 - 이 창 재
 */

#include "VGLevelTransferVolume.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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
	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, TransferLevelName);
	}
}