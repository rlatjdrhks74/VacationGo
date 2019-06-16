/* VGWeapon.h
 * Description : 캐릭터가 드는 무기에 대한 액터
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

	float GetAttackRange() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRange;
};
