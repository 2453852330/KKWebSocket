// Fill out your copyright notice in the Description page of Project Settings.


#include "KKWebSocketBPLib.h"
#include "WebSocketObject.h"


UWebSocketObject* UKKWebSocketBPLib::KK_CreateWebSocket(FString Url,const TArray<FString> & Protocols , const TMap<FString,FString> & Headers)
{
	UWebSocketObject * obj = NewObject<UWebSocketObject>();
	obj->InitWebSocket(Url,Protocols,Headers);
	return obj;
}

void UKKWebSocketBPLib::KK_CloseWebSocket(UWebSocketObject* Obj, FString Reason)
{
	if (Obj)
	{
		Obj->CloseWebSocket(Reason);
	}
}
