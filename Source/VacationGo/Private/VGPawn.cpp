/* VGPawn.cpp
 * Description : 플레이어가 조종하는 액터 폰 생성
 * ver 0.1 : 폰 초기 구성 - 이 창 재
 * ver 0.5 : 폰의 각종 컴포넌트 생성 및 움직임을 위한 입력 처리 함수 구현 - 이 창 재
 */

#include "VGPawn.h"

// Sets default values
AVGPawn::AVGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 폰의 움직임을 담당하는 충돌 컴포넌트
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	// 캐릭터 애셋을 보여주고 추가로 애니메이션 담당
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	
	// 플레이어의 입력에 따라 캐릭터가 움직이도록 설정해주는 컴포넌트
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	
	// 삼인칭 시점으로 카메라 구도를 설정할 수 있는 컴포넌트
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	
	// 게임 화면을 플레이어의 화면으로 전송
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

	// 블루프린트 설정
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

// 폰과 플레이어 컨트롤러가 생성되는 시점 파악
void AVGPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// 폰에 빙의를 진행하는 시점 파악
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

// 폰의 움직임을 위한 입력처리 함수
void AVGPawn::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

// 폰의 움직임을 위한 입력처리 함수
void AVGPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}
