/* Fountain.h
 * Description : 분수대 액터 코드
 * ver 0.1 : 분수대 초기 구성 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class VACATIONGO_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 분수대는 구조물과 물이라는 두 가지 요소로 구성
	// 언리얼 실행 환경이 선언한 객체를 자동으로 관리하게 만들기 위해 UPROPERY 매크로 선언
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	// 조명과 물의 이펙트를 추가하기 위한 요소
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash;

	// 정수 유형의 멤버 변수
	UPROPERTY(EditAnywhere, Category=ID)
	int32 ID;
};
