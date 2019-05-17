/* VacationGo.cpp
 * Description : 프로젝트 설정
 * ver 0.1 : 초기 구성 및 로그 기능 추가 - 이 창 재
 * ver 0.2 : 캐릭터의 스테이트 설정 - 이 창 재
 */

#pragma once

#include "EngineMinimal.h"

// PREINIT 스테이트 : 캐릭터 생성 전의 스테이트.
// LOADING 스테이트 : 선택한 캐릭터 애셋을 소딩하는 스테이트. 
// READY 스테이트 : 캐릭터 애셋 로딩이 완료된 스테이트. 
//                         플레이어 컨트롤러는 캐릭터를 조종할 수 있고 AI 컨트롤러는 NPC를 동작시킨다.
// DEAD 스테이트 : 캐릭터가 HP를 소진해 사망할때 발생하는 스테이트. 
//                       죽는 애니메이션을 재생하고 UI를 끄며, 충돌기능을 없애고 대미지를 입지 않도록 설정. 
//                       컨트롤러가 플레이어일 경우 입력을 비활성화, AI인 경우에는 비헤비어 트리 로직을 중지.

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

DECLARE_LOG_CATEGORY_EXTERN(VacationGo, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(VacationGo, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(VacationGo, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define ABCHECK(Expr, ...) {if(!(Expr)) {ABLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}