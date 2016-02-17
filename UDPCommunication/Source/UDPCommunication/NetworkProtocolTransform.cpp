// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPCommunication.h"
#include "NetworkProtocolTransform.h"

UNetworkProtocolTransform::UNetworkProtocolTransform(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UNetworkProtocolTransform::Parse(const FArrayReaderPtr& Reader)
{
	FTransformData Data;
	*Reader << Data;

	Stack.Add(Data);

	return true;
}

bool UNetworkProtocolTransform::GetLatest(FTransformData& Data)
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

void UNetworkProtocolTransform::Clear()
{
	Stack.Empty();
}
