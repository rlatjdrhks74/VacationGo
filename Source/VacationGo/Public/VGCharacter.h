/* VGCharacter.h
 * Description : �ΰ��� ���� ȿ�������� �����ϱ� ���� ��
 * ver 0.1 : ĳ���� �ʱ� ���� �� ��Ʈ���� ���� ������ ���� - �� â ��
 * ver 0.2 : GTA ��� �� ��ƺ��� ��� ��Ʈ�� ���� - �� â ��
 * ver 0.3 : ���� �� ���� �� �޺� ���� - �� â ��
 * ver 0.5 : �浹 ���� �� ���� ���� ǥ��, ������ ���� ���� - �� â ��
 * ver 0.6 : ������ �ڽ��� �浹�� ���� ���Ⱑ ������ ���Ⱑ ��������� ���� - �� â ��
 * ver 0.65 : ĳ���� ������ ���� �ν��Ͻ��� �����ϵ��� ���� - �� â ��
 * ver 0.7 : HP�� ����
 * ver 0.85 : NPC�� ���� ���� ��Ʈ�� ���� - �� â ��
 * ver 0.86 : ���� �½�ũ�� ���� ��������Ʈ ���� - �� â ��
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Character.h"
#include "VGCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class VACATIONGO_API AVGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		GTA,
		DIABLO,
		NPC
	};

	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	// ī�޶��� �ε巯�� ��ȯ�� ���� ����
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CanSetWeapon();
	void SetWeapon(class AVGWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AVGWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UVGCharacterStatComponent* CharacterStat;

	// private���� ����� ������Ʈ�� �����Ϳ� �����ϱ� ����
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

	void ViewChange();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	void OnAssetLoadCompleted();

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UVGAnimInstance* VGAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	int32 AssetIndex = 0;
	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;
};