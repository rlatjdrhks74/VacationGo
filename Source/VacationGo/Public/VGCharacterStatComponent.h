/* VGCharacterStatComponent.h
 * Description : 캐릭터 스텟 컴포넌트
 */

#pragma once

#include "VacationGo.h"
#include "Components/ActorComponent.h"
#include "VGCharacterStatComponent.generated.h"

// HP가 0가 됨을 알리기 위한 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
// HP값이 변할 때마다 프로그레시브바 내용을 업데이트 하기 위한 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VACATIONGO_API UVGCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVGCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
		
public:
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack();
	float GetHPRatio();
	int32 GetDropExp() const;

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;

private:
	struct FVGCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPirvateAccess = true))
	float CurrentHP;
};
