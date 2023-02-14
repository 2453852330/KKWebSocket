// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KKWebSocketBPLib.generated.h"

class UWebSocketObject;
/**
 * 
 */
UCLASS()
class KKWEBSOCKET_API UKKWebSocketBPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	static UWebSocketObject * KK_CreateWebSocket(FString Url,const TArray<FString> & Protocols , const TMap<FString,FString> & Headers);

	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	static void KK_CloseWebSocket(UWebSocketObject * Obj , FString Reason );
};
