/* VGCharacterSetting.h
 * Description : 캐릭터 에셋 관리
 * ver 0.1 : 코드 구성 - 이 창 재
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
