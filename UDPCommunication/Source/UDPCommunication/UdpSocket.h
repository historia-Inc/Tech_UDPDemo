// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "NetworkProtocolInterface.h"
#include "UdpSocket.generated.h"

/**
 * 
 */
UCLASS()
class UDPCOMMUNICATION_API UUdpSocket : public UObject
{
	GENERATED_BODY()
	
public:
	UUdpSocket();
	UUdpSocket(const FObjectInitializer& ObjectInitializer);

public:
	/**
	* 初期化処理
	* @param Ip IPアドレス
	* @param Port ポート番号
	* @param Protocol プロトコル
	*/
	bool Init(const FString& Ip, int32 Port, INetworkProtocolInterface* Protocol);

	/**
	* 終了処理
	*/
	void Shutdown();

private:
	/**
	* ソケットを作成
	*/
	bool CreateSocket();

	/**
	* ソケットを削除
	*/
	void DeleteSocket();

	/**
	* 受信者を作成
	*/
	bool CreateReceiver();

	/**
	* 受信者を削除
	*/
	void DeleteReceiver();
	
	/**
	* データ受け取りコールバック
	* @param Reader 読み取りデータ
	* @param Sender 発信者
	*/
	void OnDataReceived(const FArrayReaderPtr& Reader, const FIPv4Endpoint& Sender);

private:
	FString Ip;
	FIPv4Address IpAddress;
	int32 Port;
	INetworkProtocolInterface* Protocol;

	FSocket* Socket;
	FUdpSocketReceiver* Receiver;
};
