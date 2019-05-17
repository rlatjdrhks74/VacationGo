/* VGCharacter.h
 * Description : 인간형 폰을 효과적으로 제작하기 위한 모델
 * ver 0.1 : 캐릭터 초기 구성 및 컨트롤을 통한 움직임 구성 - 이 창 재
 * ver 0.2 : GTA 방식 및 디아블로 방식 컨트롤 구현 - 이 창 재
 * ver 0.3 : 점프 및 공격 및 콤보 구현 - 이 창 재
 * ver 0.5 : 충돌 설정 및 어택 범위 표현, 데미지 전달 설정 - 이 창 재
 * ver 0.6 : 아이템 박스와 충돌시 기존 무기가 없으면 무기가 쥐어지도록 설정 - 이 창 재
 * ver 0.65 : 캐릭터 스텟을 게임 인스턴스에 전달하도록 설정 - 이 창 재
 * ver 0.7 : HP바 구현
 * ver 0.85 : NPC를 위한 동작 컨트롤 설정 - 이 창 재
 * ver 0.86 : 공격 태스크를 위한 델리게이트 선언 - 이 창 재
 * ver 0.9 : 각 스테이트별 기본 로직 및 함수 구현 - 이 창 재
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
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	int32 GetExp() const;
	float GetFinalAttackRange() const;

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

	// 카메라의 부드러운 전환을 위한 설정
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

	// private으로 선언된 컴포넌트의 포인터에 접근하기 위함
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

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	bool bIsPlayer;

	UPROPERTY()
	class AVGAIController* VGAIController;

	UPROPERTY()
	class AVGPlayerController* VGPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
	float DeadTimer;

	FTimerHandle DeadTimerHandle = { };
};
