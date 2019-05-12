/* VGWeapon.cpp
 * Description : 캐릭터가 드는 무기에 대한 액터
 * ver 0.1 : 액터 초기 구성 - 이 창 재
 */

#include "VGWeapon.h"

// Sets default values
AVGWeapon::AVGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 초기 무기 설정
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	// 충돌 설정을 NoCollision으로 설정
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AVGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
