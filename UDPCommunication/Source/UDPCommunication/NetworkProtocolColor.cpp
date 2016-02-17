// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPCommunication.h"
#include "NetworkProtocolColor.h"

UNetworkProtocolColor::UNetworkProtocolColor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UNetworkProtocolColor::Parse(const FArrayReaderPtr& Reader)
{
	FColorData Data;
	*Reader << Data;

	Stack.Add(Data);

	return true;
}

bool UNetworkProtocolColor::GetLatest(FColorData& Data)
{
	if (Stack.Num() <= 0)
	{
		return false;
	}

	float LatestTimeStamp = 0.0f;
	for (auto Item : Stack)
	{
		if (Item.TimeStamp <= LatestTimeStamp) continue;
		Data = Item;
		LatestTimeStamp = Item.TimeStamp;
	}

	return true;
}

void UNetworkProtocolColor::Clear()
{
	Stack.Empty();
}
