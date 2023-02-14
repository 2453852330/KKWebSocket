// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebSocketObject.generated.h"

class IWebSocket;

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnKKWebSocketClose,int32 , StatusCode , const FString& , Reason , bool , bWasClean );
DECLARE_DYNAMIC_DELEGATE(FOnKKWebSocketExec);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnKKWebSocketMessage,const FString & , Message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnKKWebSocketRawMessage,const TArray<uint8> & , Data , int32, BytesRemaining);

UCLASS()
class KKWEBSOCKET_API UWebSocketObject : public UObject
{
	GENERATED_BODY()

public:

	TSharedPtr<IWebSocket> WebSocket = nullptr;
	
	void InitWebSocket(FString Url,const TArray<FString> & Protocols , const TMap<FString,FString> & Headers);
	void CloseWebSocket(FString Reason);
	
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * KK_Connect();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="KKWebSocket")
	UWebSocketObject * KK_IsConnected(bool & bResult);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * KK_SendMessage(FString Data);	
	
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnClosed(FOnKKWebSocketClose OnClosedEvent);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnConnected(FOnKKWebSocketExec OnConnectedEvent);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnMessage(FOnKKWebSocketMessage OnMessageEvent);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnConnectionError(FOnKKWebSocketMessage OnConnectionErrorEvent);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnMessageSend(FOnKKWebSocketMessage OnMessageSentEvent);
	UFUNCTION(BlueprintCallable,Category="KKWebSocket")
	UWebSocketObject * BindEventOnRawMessage(FOnKKWebSocketRawMessage OnRawMessageEvent);
};
