#pragma once

#ifndef _RECURRENTNETWORKINTERFACE_H_
#define _RECURRENTNETWORKINTERFACE_H_

// Library includes
#include <memory>

// Forward declarations
class LayeredNetwork;

// Specifies a recurrent network
class RecurrentNetworkInterface 
{
private:
public:	
	virtual ~RecurrentNetworkInterface() {};
	// The network should have a unfolding method (to convert the recurrent network into a layered one)
	virtual std::unique_ptr<LayeredNetwork> unfold(int instanceCount) = 0;
};

#endif
