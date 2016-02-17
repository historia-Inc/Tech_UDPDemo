#pragma once 

#include "Networking.h"
#include "NetworkProtocolInterface.generated.h"

UINTERFACE()
class UDPCOMMUNICATION_API UNetworkProtocolInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UDPCOMMUNICATION_API INetworkProtocolInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/**
	* プロトコル別パース処理
	*/
	virtual bool Parse(const FArrayReaderPtr& Reader) { return false; }
};