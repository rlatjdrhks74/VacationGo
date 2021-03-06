/* VGItemBox.cpp
 * Description : 아이템 박스 액터
 * ver 0.1 : 액터 초기 구성 - 이 창 재
 * ver 0.15 : 캐릭터와 박스사이의 콜리전 디텍션 설정 - 이 창 재
 * ver 0.3 : 아이템 박스 획득시 무기가 들려있지 않으면 랜덤한 무기를 쥐도록 구현 - 이 창 재
 * ver 0.5 : 사냥 컨텐츠 삭제로 무기 대신 경험치가 올라가도록 구현 - 이 창 재
 */

#include "VGItemBox.h"
#include "VGWeapon.h"
#include "VGCharacter.h"

// Sets default values
AVGItemBox::AVGItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	// 아이템 박스 메시를 불러와 설정
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));

	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	// 아이템 박스 획득시 파티클 시스템 설정
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = AVGWeapon::StaticClass();
}

// Called when the game starts or when spawned
void AVGItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVGItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AVGItemBox::OnCharacterOverlap);
}

void AVGItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Warning);

	auto VGCharacter = Cast<AVGCharacter>(OtherActor);
	ABCHECK(nullptr != VGCharacter);

	// 아이템 박스 획득시 경험치가 증가하도록 구현
	if (VGCharacter->GetController()->IsPlayerController())
	{
		int32 Exp = VGCharacter->GetExp();
		VGCharacter->SetExp(Exp);
		ABLOG(Warning, TEXT("This Character is Player Controller. Exp is %d"), VGCharacter->GetExp());
	}

	if (nullptr != VGCharacter && nullptr != WeaponItemClass)
	{
		if (VGCharacter->CanSetWeapon())
		{
			// 무기 장착 보류
			//auto NewWeapon = GetWorld()->SpawnActor<AVGWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			//VGCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &AVGItemBox::OnEffectFinished);
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip weapon currently."), *VGCharacter->GetName());
		}
	}
}

void AVGItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}
