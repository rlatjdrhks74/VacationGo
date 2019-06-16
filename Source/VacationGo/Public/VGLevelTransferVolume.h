/* VGLevelTransferVolume.h
 * Description : 레벨간 이동을 위한 볼륨
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Actor.h"
#include "VGLevelTransferVolume.generated.h"

UCLASS()
class VACATIONGO_API AVGLevelTransferVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVGLevelTransferVolume();
	void BindPlayerState(class AVGPlayerState* PlayerState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 ToggleHidden;

	UPROPERTY()
	class UBoxComponent* TransferVolume;

	UPROPERTY()
	class AVGPlayerState* VGPlayerState;
};
