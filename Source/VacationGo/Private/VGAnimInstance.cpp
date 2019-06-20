/* VGAnimInstance.cpp
 * Description : ĳ���Ͱ� ó�� ��Ȳ�� ���� ������ �ִϸ��̼��� ����ϵ��� �ϱ� ���� �ִ� �ν��Ͻ�
 * ver 0.1 : �ִ� �ν��Ͻ� �ʱ� ���� - �� â ��
 * ver 0.3 : ��������Ʈ �� ��Ÿ�� ���� - �� â ��
 * ver 0.5 : ���� ��� �� �޺� ���� - �� â ��
 * ver 0.6 : �׾����� ���̽� �� ��� �߰� - �� â ��
 */

#include "VGAnimInstance.h"

UVGAnimInstance::UVGAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	// ���� ����� ���� �ִϸ��̼� ��Ÿ��
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Book/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));

	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UVGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

// ���� ��� ��Ÿ�� ����
void UVGAnimInstance::PlayAttackMontage()
{
	ABCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0f);
}

// ��������Ʈ ���
void UVGAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UVGAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UVGAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UVGAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

