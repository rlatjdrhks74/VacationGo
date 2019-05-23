/* VGLevelTransferVolume.h
 * Description : ������ �̵��� ���� ����
 * ver 0.1 : transfer ���� ���� - �� â ��
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;

	UPROPERTY()
	class UBoxComponent* TransferVolume;
};
