// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "engine/AssetManager.h"
#include "DrawDebugHelpers.h"				//Debug

#include "Blueprint/AIBlueprintHelperLibrary.h"	//�׺�޽� �̵�
//#include "Blueprint/SlateBlueprintLibrary.h"	//blueprint function library
#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FindMine, Log, All);	///�ش� ī�װ��� �̿��ؼ� �α׸� ����ϰԲ� �ϴ°�
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))		//__FUNTION__ : ���� �� �α׸� ����ϴ� �Լ� �̸��� �ǹ��Ѵ�
#define LOG(Format, ...) UE_LOG(FindMine, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float Time, const FColor& Color, const FString& Text);


// ====== Enum =========


UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	Knight,
	Magicion,
	Acher,
	Thif,
	End,
};

UENUM(BlueprintType)
enum class ETriggerType : uint8
{
	Box,
	Capsule,
	Sphere,
	End,
};

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8
{
	Trace,
	Attack,
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Box,
	Cone,
	Sphere,
	Projectile,
	Buff,
	End,
};

USTRUCT()
struct FAssetPathInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Name")
	FString		Name;

	UPROPERTY(EditAnywhere, Category = "Path")
	FSoftObjectPath		Path;
};

template <typename UENUMTYPE>FString UEnumToString(UENUMTYPE enumValue){	FString text = typeid(UENUMTYPE).name();	text.ReplaceInline(TEXT("enum "), TEXT(""));	LOG(TEXT("%s"), *text);	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *text, true);	if (!enumPtr)		return FString("Invalid");	return enumPtr->GetNameStringByIndex(static_cast<int32>(enumValue));}