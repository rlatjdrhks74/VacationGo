/* VGCharacter.cpp
 * Description : �ΰ��� ���� ȿ�������� �����ϱ� ���� ��
 * ver 0.1 : ĳ���� �ʱ� ���� �� ��Ʈ���� ���� ������ ���� - �� â ��
 * ver 0.2 : GTA ��� �� ��ƺ�� ��� ��Ʈ�� ���� - �� â ��
 * ver 0.3 : ���� �� ���� �� �޺� ���� - �� â ��
 * ver 0.5 : �浹 ���� �� ���� ���� ǥ��, ������ ���� ���� -  �� â ��
 * ver 0.55 : �������� �����Ǿ����� �״� �ִ� ���� - �� â ��
 * ver 0.6 : ������ �ڽ��� �浹�� ���� ���Ⱑ ������ ���Ⱑ ��������� ���� - �� â ��
 * ver 0.65 : ĳ���� ������ ���� �ν��Ͻ��� �����ϵ��� ���� - �� â ��
 * ver 0.7 : HP�� ���� �� �������� ���� - �� â ��
 * ver 0.8 : NPC ������ ���� AI ��Ʈ�ѷ� ���� - �� â ��
 * ver 0.85 : NPC�� ���� ���� ��Ʈ�� ���� - �� â ��
 * ver 0.86 : ���� �½�ũ�� ���� ��������Ʈ ���� - �� â ��
 * ver 0.9 : NPC ���� ����ȭ - �� â ��
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

// Sets default values
AVGCharacter::AVGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����Ī �������� ī�޶� ������ ������ �� �ִ� ������Ʈ
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	// ���� ȭ���� �÷��̾��� ȭ������ ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// ĳ���� ���� ������Ʈ ����
	CharacterStat = CreateDefaultSubobject<UVGCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	// HP�� ���� ����
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
	GetCharacterMovement()->JumpZVelocity = 800.0f;

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

	// �����Ǵ� ĳ���ͺ��� AI ��Ʈ�ѷ��� ��ġ
	AIControllerClass = AVGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AVGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	auto CharacterWidget = Cast<UVGCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}

	if (!IsPlayerControlled())
	{
		auto DefaultSetting = GetDefault<UVGCharacterSetting>();
		int32 RandIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
		CharacterAssetToLoad = DefaultSetting->CharacterAssets[RandIndex];
		auto VGGameInstance = Cast<UVGGameInstance>(GetGameInstance());
		if (nullptr != VGGameInstance)
		{
			AssetStreamingHandle = VGGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &AVGCharacter::OnAssetLoadCompleted));
		}
	}
}

// ��Ʈ�� ��� ���� ���
void AVGCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	// GTA ���
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
	// ��ƺ�� ���
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

// ��������Ʈ ���ε� �۾� �Լ�
void AVGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	VGAnim = Cast<UVGAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != VGAnim);

	VGAnim->OnMontageEnded.AddDynamic(this, &AVGCharacter::OnAttackMontageEnded);

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

// ������ ���� �Լ�
float AVGCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);
	CharacterStat->SetDamage(FinalDamage);
	//if (CurrentState == ECharacterState::DEAD)
	//{
	//	if (EventInstigator->IsPlayerController())
	//	{
	//		auto ABPlayerController = Cast<AVGPlayerController>(EventInstigator);
	//		ABCHECK(nullptr != ABPlayerController, 0.0f);
	//		ABPlayerController->NPCKill(this);
	//	}
	//}

	return FinalDamage;
}

// NPC�� �ڿ������� ������ ���� ���� ��Ʈ�ѷ� ����
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
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

// Called to bind functionality to input
void AVGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Ư�� �Է� ó��
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AVGCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AVGCharacter::Attack);

	// �⺻ ���� �Է�ó��
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AVGCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AVGCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AVGCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AVGCharacter::LookUp);
}

// ���� ���� ���� �Լ�
bool AVGCharacter::CanSetWeapon()
{
	return true;
}

// ���� ���� �Լ�
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

// ���� �⺻ ���� �Է�ó�� �Լ�
void AVGCharacter::UpDown(float NewAxisValue)
{
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

void AVGCharacter::LeftRight(float NewAxisValue)
{
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


// Ư�� �Է� ó�� �Լ�
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

// ���� ���� �Լ���
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
{/*
	float FinalAttackRange = GetFinalAttackRange();*/

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
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
	if (LoadedAssetPath.IsValid())
	{
		GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	}
}