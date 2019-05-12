/* VGPawn.cpp
 * Description : �÷��̾ �����ϴ� ���� �� ����
 * ver 0.1 : �� �ʱ� ���� - �� â ��
 * ver 0.5 : ���� ���� ������Ʈ ���� �� �������� ���� �Է� ó�� �Լ� ���� - �� â ��
 */

#include "VGPawn.h"

// Sets default values
AVGPawn::AVGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� �������� ����ϴ� �浹 ������Ʈ
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	// ĳ���� �ּ��� �����ְ� �߰��� �ִϸ��̼� ���
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	
	// �÷��̾��� �Է¿� ���� ĳ���Ͱ� �����̵��� �������ִ� ������Ʈ
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	
	// ����Ī �������� ī�޶� ������ ������ �� �ִ� ������Ʈ
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	
	// ���� ȭ���� �÷��̾��� ȭ������ ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Barbarous.SK_CharM_Barbarous"));

	if (SK_CARDBOARD.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	// �������Ʈ ����
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/PeopleAnimBlueprint.PeopleAnimBlueprint_C"));

	if (WARRIOR_ANIM.Succeeded())
	{
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AVGPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ���� �÷��̾� ��Ʈ�ѷ��� �����Ǵ� ���� �ľ�
void AVGPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// ���� ���Ǹ� �����ϴ� ���� �ľ�
void AVGPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AVGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AVGPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AVGPawn::LeftRight);
}

// ���� �������� ���� �Է�ó�� �Լ�
void AVGPawn::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

// ���� �������� ���� �Է�ó�� �Լ�
void AVGPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}
