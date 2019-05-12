/* VGPawn.h
 * Description : 플레이어가 조종하는 액터 폰 생성
 * ver 0.1 : 폰 초기 구성 - 이 창 재
 * ver 0.5 : 폰의 각종 컴포넌트 생성 및 움직임을 위한 입력 처리 함수 구현 - 이 창 재
 */

#pragma once

#include "VacationGo.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "VGPawn.generated.h"

UCLASS()
class VACATIONGO_API AVGPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVGPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
};
