// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "NetworkProtocolTransform.h"
#include "NetworkProtocolColor.h"
#include "UDPCommunicationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UDPCOMMUNICATION_API AUDPCommunicationGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AUDPCommunicationGameMode();
	AUDPCommunicationGameMode(const FObjectInitializer& ObjectInitializer);

public:
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	/**
	* 初期化処理
	*/
	virtual void Init();

	/**
	* 終了処理
	*/
	virtual void Shutdown();

	/**
	* Transformプロトコル取得
	*/
	UFUNCTION(BlueprintPure, Category = "Network")
		UNetworkProtocolTransform* GetTransformProtocol() const { return TransformProtocol; }

	/**
	* Transformプロトコル取得
	*/
	UFUNCTION(BlueprintPure, Category = "Network")
		UNetworkProtocolColor* GetColorProtocol() const { return ColorProtocol; }
private:
	/**
	* Transformプロトコル初期化処理
	*/
	bool InitTransformProtocol();

	/**
	* Transformプロトコル終了処理
	*/
	void ShutdownTransformProtocol();

	/**
	* Colorプロトコル初期化処理
	*/
	bool InitColorProtocol();

	/**
	* Colorプロトコル終了処理
	*/
	void ShutdownColorProtocol();

private:
	/** Transformプロトコル */
	UPROPERTY()
	class UNetworkProtocolTransform* TransformProtocol;

	/** Colorプロトコル */
	UPROPERTY()
	class UNetworkProtocolColor* ColorProtocol;

	/** Transformソケット */
	UPROPERTY()
	class UUdpSocket* TransformUdpSocket;

	/** Colorソケット */
	UPROPERTY()
	class UUdpSocket* ColorUdpSocket;
	
	
};
