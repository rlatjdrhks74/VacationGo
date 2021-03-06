/* VGCharacter.cpp
 * Description : 인간형 폰을 효과적으로 제작하기 위한 모델
 * ver 0.1 : 캐릭터 초기 구성 및 컨트롤을 통한 움직임 구성 - 이 창 재
 * ver 0.2 : GTA 방식 및 디아블로 방식 컨트롤 구현 - 이 창 재
 * ver 0.3 : 점프 및 공격 및 콤보 구현 - 이 창 재
 * ver 0.5 : 충돌 설정 및 어택 범위 표현, 데미지 전달 설정 -  이 창 재
 * ver 0.55 : 데미지가 누적되었을때 죽는 애님 구현 - 이 창 재
 * ver 0.6 : 아이템 박스와 충돌시 기존 무기가 없으면 무기가 쥐어지도록 설정 - 이 창 재
 * ver 0.65 : 캐릭터 스텟을 게임 인스턴스에 전달하도록 설정 - 이 창 재
 * ver 0.7 : HP바 구현 및 위젯과의 연결 - 이 창 재
 * ver 0.8 : NPC 구현을 위한 AI 컨트롤러 연결 - 이 창 재
 * ver 0.85 : NPC를 위한 동작 컨트롤 설정 - 이 창 재
 * ver 0.86 : 공격 태스크를 위한 델리게이트 구성 - 이 창 재
 * ver 0.88 : NPC 에셋 랜덤화 - 이 창 재
 * ver 0.9 : 각 스테이트별 기본 로직 및 함수 구현 - 이 창 재
 * ver 0.92 : 플레이어 스테이트 반영 및 HUB에 연동 - 이 창 재
 * ver 0.95 : 공격시 이동 속도 차이를 두어 모션 보완 - 이 창 재
 */

#include "VGCharacter.h"
#include "VGAnimInstance.h"
#include "VGWeapon.h"
#include "VGCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "VGCharacterWidget.h"
#include "VGAIController.h"
#include "VGCharacterSetting.h"
#include "VGGameInstance.h"
#include "VGPlayerController.h"
#include "VGPlayerState.h"
#include "VGHUDWidget.h"

// Sets default values
AVGCharacter::AVGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 삼인칭 시점으로 카메라 구도를 설정할 수 있는 컴포넌트
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	// 게임 화면을 플레이어의 화면으로 전송
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// 캐릭터 스텟 컴포넌트 생성
	CharacterStat = CreateDefaultSubobject<UVGCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	// HP바 위젯 구현
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Barbarous.SK_CharM_Barbarous"));

	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/PeopleAnimBlueprint.PeopleAnimBlueprint_C"));

	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	SetControlMode(EControlMode::GTA);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 550.0f;

	IsAttacking = false;
	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("VGCharacter"));
	AttackRange = 80.0f;
	AttackRadius = 50.0f;

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	// 생성되는 캐릭터별로 AI 컨트롤러를 배치
	AIControllerClass = AVGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 상황별 스테이트 머신 지정
	AssetIndex = 4;

	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	bCanBeDamaged = false;

	DeadTimer = 5.0f;
}

// Called when the game starts or when spawned
void AVGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 캐릭터가 플레이어인지 NPC인지에 따라 각자의 컨트롤러 구성
	bIsPlayer = IsPlayerControlled();
	if (bIsPlayer)
	{
		VGPlayerController = Cast<AVGPlayerController>(GetController());
		ABCHECK(nullptr != VGPlayerController);
	}
	else
	{
		VGAIController = Cast<AVGAIController>(GetController());
		ABCHECK(nullptr != VGAIController);
	}

	// 캐릭터 에셋이 설정된 CharacterSetting을 불러온다.
	auto DefaultSetting = GetDefault<UVGCharacterSetting>();

	// 플레이어인 경우 세이브데이터에서 사용자가 선택했던 에셋 인덱스를 불러와 해당 에셋을 세팅
	if (bIsPlayer)
	{
		auto VGPlayerState = Cast<AVGPlayerState>(GetPlayerState());
		ABCHECK(nullptr != VGPlayerState);
		AssetIndex = VGPlayerState->GetCharacterIndex();
	}
	else
	{
		// AI인 경우 랜덤한 에셋 번호를 생성하여 세팅
		AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	}

	CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];
	auto VGGameInstance = Cast<UVGGameInstance>(GetGameInstance());
	ABCHECK(nullptr != VGGameInstance);
	AssetStreamingHandle = VGGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &AVGCharacter::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);
}

void AVGCharacter::SetCharacterState(ECharacterState NewState)
{
	ABCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		if (bIsPlayer)
		{
			DisableInput(VGPlayerController);

			// 게임 UI HUB를 짜는데 쓰일 캐릭터 스텟을 바인딩
			VGPlayerController->GetHUDWidgetWithCreation()->BindCharacterStat(CharacterStat);

			auto VGPlayerState = Cast<AVGPlayerState>(GetPlayerState());
			ABCHECK(nullptr != VGPlayerState);
			CharacterStat->SetNewLevel(VGPlayerState->GetCharacterLevel());
		}
		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = false;
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		// HP바는 현재상으로는 필요없다고 가정
		HPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = true;

		CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			SetCharacterState(ECharacterState::DEAD);
			});

		auto CharacterWidget = Cast<UVGCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		ABCHECK(nullptr != CharacterWidget);
		CharacterWidget->BindCharacterStat(CharacterStat);

		if (bIsPlayer)
		{
			SetControlMode(EControlMode::GTA);
			EnableInput(VGPlayerController);
		}
		else
		{
			SetControlMode(EControlMode::NPC);
			GetCharacterMovement()->MaxWalkSpeed = 60.0f;
			VGAIController->RunAI();
			// 인간형 AI는 공격당하지 않는다고 가정
			bCanBeDamaged = false;
		}

		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		VGAnim->SetDeadAnim();
		bCanBeDamaged = false;

		if (bIsPlayer)
		{
			DisableInput(VGPlayerController);
		}
		else
		{
			VGAIController->StopAI();
		}

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {

			if (bIsPlayer)
			{
				VGPlayerController->RestartLevel();
			}
			else
			{
				Destroy();
			}

			}), DeadTimer, false);

		break;
	}
	}
}

ECharacterState AVGCharacter::GetCharacterState() const
{
	return CurrentState;
}

int32 AVGCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
}

float AVGCharacter::GetFinalAttackRange() const
{
	return (nullptr != CurrentWeapon) ? CurrentWeapon->GetAttackRange() : AttackRange;
}

// 카메라 방향 및 컨트롤 모드 변경 기능
void AVGCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	// GTA 방식 (카메라 회전)
	case EControlMode::GTA:
		//SpringArm->TargetArmLength = 450.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	// 디아블로 방식 (카메라 회전 고정)
	case EControlMode::DIABLO:
		//SpringArm->TargetArmLength = 800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::NPC:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		break;
	}
}


// Called every frame
void AVGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		break;
	}

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

// 델리게이트 바인딩 작업 함수
void AVGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	VGAnim = Cast<UVGAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != VGAnim);

	VGAnim->OnMontageEnded.AddDynamic(this, &AVGCharacter::OnAttackMontageEnded);

	// 콤보 구현
	VGAnim->OnNextAttackCheck.AddLambda([this]() -> void {

		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			VGAnim->JumpToAttackMontageSection(CurrentCombo);
		}
		});

	VGAnim->OnAttackHitCheck.AddUObject(this, &AVGCharacter::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		ABLOG(Warning, TEXT("OnHPIsZero"));
		VGAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
}

// 데미지 전달 함수
float AVGCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);
	CharacterStat->SetDamage(FinalDamage);
	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			auto VGPlayerController = Cast<AVGPlayerController>(EventInstigator);
			ABCHECK(nullptr != VGPlayerController, 0.0f);
			VGPlayerController->NPCKill(this);
		}
	}

	return FinalDamage;
}

// NPC의 자연스러운 동작을 위한 동작 컨트롤러 설정
void AVGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsPlayerControlled())
	{
		SetControlMode(EControlMode::GTA);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else
	{
		SetControlMode(EControlMode::NPC);
		GetCharacterMovement()->MaxWalkSpeed = 60.0f;
	}
}

// Called to bind functionality to input
void AVGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 특수 입력 처리
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AVGCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AVGCharacter::Attack);

	// 기본 동작 입력처리
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AVGCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AVGCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AVGCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AVGCharacter::LookUp);
}

// 경험치 업
void AVGCharacter::SetExp(int32 exp)
{
	if (GetController()->IsPlayerController())
	{
		auto VGPlayerController = Cast<AVGPlayerController>(GetController());
		VGPlayerController->ExpUp(exp);
	}
}

// 무기 장착 가능 함수
bool AVGCharacter::CanSetWeapon()
{
	return true;
}

// 무기 장착 함수
void AVGCharacter::SetWeapon(AVGWeapon* NewWeapon)
{
	ABCHECK(nullptr != NewWeapon);

	if (nullptr != CurrentWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

// 폰의 기본 동작 - 위 아래 이동
void AVGCharacter::UpDown(float NewAxisValue)
{
	if (IsAttacking)
	{
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
}

// 폰의 기본 동작 - 왼쪽 오른쪽 이동
void AVGCharacter::LeftRight(float NewAxisValue)
{
	if (IsAttacking)
	{
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
}

// 폰의 기본 동작 - 회전
void AVGCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void AVGCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}


// 특수 입력 - 카메라 방향 변경
void AVGCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}
}

// 특수 입력 - 공격
void AVGCharacter::Attack()
{
	if (IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();
		VGAnim->PlayAttackMontage();
		VGAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

// 공격 구현 함수들
void AVGCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();

	OnAttackEnd.Broadcast();
}

void AVGCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void AVGCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AVGCharacter::AttackCheck()
{
	float FinalAttackRange = GetFinalAttackRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * FinalAttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}

void AVGCharacter::OnAssetLoadCompleted()
{
	AssetStreamingHandle->ReleaseHandle();
	TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(CharacterAssetToLoad);
	ABCHECK(LoadedAssetPath.IsValid());

	GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	SetCharacterState(ECharacterState::READY);
}