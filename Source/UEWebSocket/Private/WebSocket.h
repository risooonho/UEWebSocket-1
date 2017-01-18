// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
//
// libwebsocket client wrapper. 
//
#pragma  once
#include "UEWebSocketPrivatePCH.h"

class FMyWebSocket
{

public: 

	// Initialize as client side socket. 
	FMyWebSocket(const FString& url,int port);

	// Initialize as server side socket. 
	FMyWebSocket(WebSocketInternalContext* InContext, WebSocketInternal* Wsi);

	// clean up. 
	~FMyWebSocket();

	/************************************************************************/
	/* Set various callbacks for Socket Events                              */           
	/************************************************************************/
	void SetConnectedCallBack(FWebsocketInfoCallBack CallBack);
	void SetErrorCallBack(FWebsocketInfoCallBack CallBack);
	void SetRecieveCallBack(FWebsocketPacketRecievedCallBack CallBack);

	/** Send raw data to remote end point. */ 
	bool Send(uint8* Data, uint32 Size);

	/** service libwebsocket.			   */ 
	void Tick();
	/** service libwebsocket until outgoing buffer is empty */ 
	void Flush();

	/** Helper functions to describe end points. */
	FString RemoteEndPoint();
	FString LocalEndPoint(); 

	/* libwebsocket service functions */
	static int unreal_networking_server(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);
	static int unreal_networking_client(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);

private:

	void HandlePacket();
	void OnRawRecieve(void* Data, uint32 Size);
	void OnRawWebSocketWritable(WebSocketInternal* wsi);

	/************************************************************************/
	/*	Various Socket callbacks											*/                                                                 
	/************************************************************************/ 
	FWebsocketPacketRecievedCallBack  RecievedCallBack; 
	FWebsocketInfoCallBack ConnectedCallBack;
	FWebsocketInfoCallBack ErrorCallBack;

	/**  Recv and Send Buffers, serviced during the Tick */
	TArray<uint8> RecievedBuffer;
	TArray<TArray<uint8>> OutgoingBuffer;

	/** libwebsocket internal context*/
	WebSocketInternalContext* Context;

	/** libwebsocket web socket */
	WebSocketInternal* Wsi;

	/** libwebsocket Protocols that can be serviced by this implemenation*/
	WebSocketInternalProtocol* Protocols;

	/** Server side socket or client side*/
	bool IsServerSide; 


	friend class FWebSocketServer;
	int SockFd;
};


