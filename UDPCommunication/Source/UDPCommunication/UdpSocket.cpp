// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPCommunication.h"
#include "UdpSocket.h"

UUdpSocket::UUdpSocket()
{
}

UUdpSocket::UUdpSocket(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUdpSocket::Init(const FString& InIp, int32 InPort, INetworkProtocolInterface* InProtocol)
{
	Ip = InIp;
	Port = InPort;
	Protocol = InProtocol;

	FIPv4Address::Parse(Ip, IpAddress);

	if (!CreateSocket())
	{
		Shutdown();
		return false;
	}

	if (!CreateReceiver())
	{
		Shutdown();
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Init UdpSocket."));
	return true;
}

void UUdpSocket::Shutdown()
{
	DeleteReceiver();

	DeleteSocket();

	UE_LOG(LogTemp, Log, TEXT("Shutdown UdpSocket."));
}

bool UUdpSocket::CreateSocket()
{
	if (IpAddress.IsMulticastAddress())
	{
		Socket = FUdpSocketBuilder(TEXT("Multicast"))
			.WithMulticastLoopback()
			.WithMulticastTtl(1)
			.JoinedToGroup(IpAddress)
			.BoundToPort(Port)
			.Build();
	}
	else
	{
		Socket = FUdpSocketBuilder(TEXT("Unicast"))
			.BoundToAddress(IpAddress)
			.BoundToPort(Port)
			.Build();
	}

	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Build Socket failed."));
		return false;
	}

	return true;
}

void UUdpSocket::DeleteSocket()
{
	if (!Socket) return;

	Socket->Close();
	delete Socket;
	Socket = nullptr;
}

bool UUdpSocket::CreateReceiver()
{
	Receiver = new FUdpSocketReceiver(Socket, FTimespan::FromMilliseconds(1), TEXT("Receiver"));

	if (!Receiver)
	{
		UE_LOG(LogTemp, Error, TEXT("Construct Receiver failed."));
		return false;
	}

	Receiver->OnDataReceived().BindUObject(this, &UUdpSocket::OnDataReceived);

	return true;
}

void UUdpSocket::DeleteReceiver()
{
	if (!Receiver) return;

	Receiver->Stop();
	delete Receiver;
	Receiver = nullptr;
}

void UUdpSocket::OnDataReceived(const FArrayReaderPtr& Reader, const FIPv4Endpoint& Sender)
{
	if (GEngine)
	{
		FString DataStr = FString::FromHexBlob(Reader->GetData(), Reader->Num());
		UE_LOG(LogTemp, Log, TEXT("%s"), *DataStr);
	}

	if (!Protocol->Parse(Reader))
	{
		UE_LOG(LogTemp, Error, TEXT("UUdpSocket::OnDataReceived failed."));
	}
}


