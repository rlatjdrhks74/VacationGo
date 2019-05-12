/* VGAnimInstance.h
 * Description : ĳ���Ͱ� ó�� ��Ȳ�� ���� ������ �ִϸ��̼��� ����ϵ��� �ϱ� ���� �ִ� �ν��Ͻ�
 * ver 0.1 : �ִ� �ν��Ͻ� �ʱ� ���� - �� â ��
 * ver 0.3 : ��������Ʈ �� ��Ÿ�� ���� - �� â ��
 * ver 0.5 : ���� ��� �� �޺� ���� - �� â ��
 * ver 0.6 : �׾����� ���̽� �� ��� �߰� - �� â ��
 */

#pragma once

#include "VacationGo.h"
#include "Animation/AnimInstance.h"
#include "VGAnimInstance.generated.h"

// ��������Ʈ ����
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
