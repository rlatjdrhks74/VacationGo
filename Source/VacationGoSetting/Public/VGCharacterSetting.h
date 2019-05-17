/* VGCharacterSetting.h
 * Description : ĳ���� ���� ����
 * ver 0.1 : �ڵ� ���� - �� â ��
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VGCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config= VacationGo)
class VACATIONGOSETTING_API UVGCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UVGCharacterSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
