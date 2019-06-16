/* VGCharacterStatComponent.h
 * Description : ĳ���� ���� ������Ʈ
 */

#pragma once

#include "VacationGo.h"
#include "Components/ActorComponent.h"
#include "VGCharacterStatComponent.generated.h"

// HP�� 0�� ���� �˸��� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
// HP���� ���� ������ ���α׷��ú�� ������ ������Ʈ �ϱ� ���� ��������Ʈ
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
