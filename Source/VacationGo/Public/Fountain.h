/* Fountain.h
 * Description : �м��� ���� �ڵ�
 * ver 0.1 : �м��� �ʱ� ���� - �� â ��
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

	// �м���� �������� ���̶�� �� ���� ��ҷ� ����
	// �𸮾� ���� ȯ���� ������ ��ü�� �ڵ����� �����ϰ� ����� ���� UPROPERY ��ũ�� ����
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	// ����� ���� ����Ʈ�� �߰��ϱ� ���� ���
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash;

	// ���� ������ ��� ����
	UPROPERTY(EditAnywhere, Category=ID)
	int32 ID;
};
