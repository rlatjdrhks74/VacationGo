/* VGGameInstance.h
 * Description : ĳ���� ������ �����ϱ� ���� ���� �ν��Ͻ�
 */

#pragma once

#include "VacationGo.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "VGGameInstance.generated.h"

USTRUCT(BlueprintType)
// ���� ����ü
struct FVGCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FVGCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};


/**
 * 
 */
UCLASS()
class VACATIONGO_API UVGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UVGGameInstance();

	virtual void Init() override;
	FVGCharacterData* GetVGCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	class UDataTable* VGCharacterTable;
};
