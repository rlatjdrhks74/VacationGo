/* VGWeapon.h
 * Description : ĳ���Ͱ� ��� ���⿡ ���� ����
 * ver 0.1 : ���� �ʱ� ���� - �� â ��
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Actor.h"
#include "VGWeapon.generated.h"

UCLASS()
class VACATIONGO_API AVGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVGWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

};
