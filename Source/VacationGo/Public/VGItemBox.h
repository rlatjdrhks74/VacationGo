/* VGItemBox.h
 * Description : 아이템 박스 액터
 * ver 0.1 : 액터 초기 구성 - 이 창 재
 * ver 0.15 : 캐릭터와 박스사이의 콜리전 디텍션 설정 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Actor.h"
#include "VGItemBox.generated.h"

UCLASS()
class VACATIONGO_API AVGItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVGItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class AVGWeapon> WeaponItemClass;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);

};
