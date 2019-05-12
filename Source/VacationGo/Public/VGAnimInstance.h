/* VGAnimInstance.h
 * Description : 캐릭터가 처한 상황에 따라 적절한 애니메이션을 재생하도록 하기 위한 애님 인스턴스
 * ver 0.1 : 애님 인스턴스 초기 구성 - 이 창 재
 * ver 0.3 : 델리게이트 및 몽타주 구성 - 이 창 재
 * ver 0.5 : 공격 모션 및 콤보 구성 - 이 창 재
 * ver 0.6 : 죽었을때 케이스 및 모션 추가 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "Animation/AnimInstance.h"
#include "VGAnimInstance.generated.h"

// 델리게이트 선언
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UVGAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void SetDeadAnim() { IsDead = true; }

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage * AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
};
