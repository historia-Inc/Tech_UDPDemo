// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPCommunication.h"
#include "UdpSocket.h"
#include "UDPCommunicationGameMode.h"


static const FString LOCALHOST_IP = TEXT("127.0.0.1");

AUDPCommunicationGameMode::AUDPCommunicationGameMode()
	: TransformProtocol(nullptr)
	, ColorProtocol(nullptr)
	, TransformUdpSocket(nullptr)
	, ColorUdpSocket(nullptr)
{
}

AUDPCommunicationGameMode::AUDPCommunicationGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TransformProtocol(nullptr)
	, ColorProtocol(nullptr)
	, TransformUdpSocket(nullptr)
	, ColorUdpSocket(nullptr)
{
}

void AUDPCommunicationGameMode::BeginPlay()
{
	Init();
	Super::BeginPlay();
}

void AUDPCommunicationGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Shutdown();
	Super::EndPlay(EndPlayReason);
}

void AUDPCommunicationGameMode::Init()
{
	if (!InitTransformProtocol())
	{
		Shutdown();
		return;
	}

	if (!InitColorProtocol())
	{
		Shutdown();
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Init Protocols."));
}

void AUDPCommunicationGameMode::Shutdown()
{
	ShutdownTransformProtocol();

	ShutdownColorProtocol();

	UE_LOG(LogTemp, Log, TEXT("Shutdown Protocols."));
}

bool AUDPCommunicationGameMode::InitTransformProtocol()
{
	TransformProtocol = NewObject<UNetworkProtocolTransform>(GetTransientPackage(), UNetworkProtocolTransform::StaticClass());

	if (!TransformProtocol)
	{
		UE_LOG(LogTemp, Error, TEXT("NewObject TransformProtocol failed."));
		return false;
	}

	TransformUdpSocket = NewObject<UUdpSocket>(GetTransientPackage(), UUdpSocket::StaticClass());

	if (!TransformUdpSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("NewObject TransformUdpSocket failed."));
		return false;
	}

	if (!TransformUdpSocket->Init(LOCALHOST_IP, 50001, TransformProtocol))
	{
		UE_LOG(LogTemp, Error, TEXT("TransformUdpSocket::Init failed."));
		return false;
	}

	return true;
}

void AUDPCommunicationGameMode::ShutdownTransformProtocol()
{
	if (TransformUdpSocket)
	{
		TransformUdpSocket->Shutdown();
		TransformUdpSocket = nullptr;
	}

	if (TransformProtocol)
	{
		TransformProtocol = nullptr;
	}
}

bool AUDPCommunicationGameMode::InitColorProtocol()
{
	ColorProtocol = NewObject<UNetworkProtocolColor>(GetTransientPackage(), UNetworkProtocolColor::StaticClass());

	if (!ColorProtocol)
	{
		UE_LOG(LogTemp, Error, TEXT("NewObject ColorProtocol failed."));
		return false;
	}

	ColorUdpSocket = NewObject<UUdpSocket>(GetTransientPackage(), UUdpSocket::StaticClass());

	if (!ColorUdpSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("NewObject ColorUdpSocket failed."));
		return false;
	}

	if (!ColorUdpSocket->Init(LOCALHOST_IP, 50002, ColorProtocol))
	{
		UE_LOG(LogTemp, Error, TEXT("ColorUdpSocket::Init failed."));
		return false;
	}

	return true;
}

void AUDPCommunicationGameMode::ShutdownColorProtocol()
{
	if (ColorUdpSocket)
	{
		ColorUdpSocket->Shutdown();
		ColorUdpSocket = nullptr;
	}

	if (ColorProtocol)
	{
		ColorProtocol = nullptr;
	}
}


