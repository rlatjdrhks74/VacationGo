/* VGWeapon.cpp
 * Description : ĳ���Ͱ� ��� ���⿡ ���� ����
 * ver 0.1 : ���� �ʱ� ���� - �� â ��
 */

#include "VGWeapon.h"

// Sets default values
AVGWeapon::AVGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// �ʱ� ���� ����
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	// �浹 ������ NoCollision���� ����
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AVGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
