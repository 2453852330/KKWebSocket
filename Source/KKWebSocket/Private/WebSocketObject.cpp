// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketObject.h"

#include "IWebSocket.h"
#include "WebSocketsModule.h"

void UWebSocketObject::InitWebSocket(FString Url,const TArray<FString> & Protocols , const TMap<FString,FString> & Headers)
{
	if (!WebSocket)
	{
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url,Protocols,Headers);
	}
}

void UWebSocketObject::CloseWebSocket(FString Reason)
{
	if (WebSocket)
	{
		WebSocket->Close(1000,Reason);
	}
	this->MarkPendingKill();
}

UWebSocketObject* UWebSocketObject::KK_Connect()
{
	if (WebSocket)
	{
		WebSocket->Connect();
	}
	return this;
}

UWebSocketObject* UWebSocketObject::KK_IsConnected(bool& bResult)
{
	if (WebSocket)
	{
		bResult = WebSocket->IsConnected();
	}
	return this;
}

UWebSocketObject* UWebSocketObject::KK_SendMessage(FString Data)
{
	if (WebSocket)
	{
		WebSocket->Send(Data);
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnClosed(FOnKKWebSocketClose OnClosedEvent)
{
	if (WebSocket)
	{
		WebSocket->OnClosed().AddLambda([OnClosedEvent](int32  StatusCode , const FString&  Reason , bool  bWasClean )
		{
			OnClosedEvent.ExecuteIfBound(StatusCode,Reason,bWasClean);
		});
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnConnected(FOnKKWebSocketExec OnConnectedEvent)
{
	if (WebSocket)
	{
		WebSocket->OnConnected().AddLambda([OnConnectedEvent]()
		{
			OnConnectedEvent.ExecuteIfBound();
		});
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnMessage(FOnKKWebSocketMessage OnMessageEvent)
{
	if (WebSocket)
	{
		WebSocket->OnMessage().AddLambda([OnMessageEvent](const FString&  MessageString )
		{
			OnMessageEvent.ExecuteIfBound(MessageString);
		});
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnConnectionError(FOnKKWebSocketMessage OnConnectionErrorEvent)
{
	if (WebSocket)
	{
		WebSocket->OnConnectionError().AddLambda([OnConnectionErrorEvent](const FString& Error  )
		{
			OnConnectionErrorEvent.ExecuteIfBound(Error);
		});
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnMessageSend(FOnKKWebSocketMessage OnMessageSentEvent)
{
	if (WebSocket)
	{
		WebSocket->OnMessageSent().AddLambda([OnMessageSentEvent]( const FString& MessageString   )
		{
			OnMessageSentEvent.ExecuteIfBound(MessageString);
		});
	}
	return this;
}

UWebSocketObject* UWebSocketObject::BindEventOnRawMessage(FOnKKWebSocketRawMessage OnRawMessageEvent)
{
	if (WebSocket)
	{
		WebSocket->OnRawMessage().AddLambda([OnRawMessageEvent](  const void* Data, SIZE_T Size, SIZE_T  BytesRemaining)
		{
			TArray<uint8> Tmp_Data((uint8*)Data,Size);
			
			OnRawMessageEvent.ExecuteIfBound(Tmp_Data,BytesRemaining);
		});
	}
	return this;
}
