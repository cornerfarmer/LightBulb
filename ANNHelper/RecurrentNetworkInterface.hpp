#pragma once

#ifndef _RECURRENTNETWORKINTERFACE_H_
#define _RECURRENTNETWORKINTERFACE_H_

// Library includes
#include <memory>

// Forward declarations
class LayeredNetwork;

class RecurrentNetworkInterface 
{
private:
public:	
	virtual ~RecurrentNetworkInterface() {};

	virtual std::unique_ptr<LayeredNetwork> unfold(int instanceCount) = 0;
};

#endif
