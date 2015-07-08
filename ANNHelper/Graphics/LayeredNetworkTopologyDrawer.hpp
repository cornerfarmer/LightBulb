#pragma once

#ifndef _LAYEREDNETWORKTOPOLOYDRAWEROPTIONS_H_
#define _LAYEREDNETWORKTOPOLOYDRAWEROPTIONS_H_

// Includes
#include "AbstractNetworkTopologyDrawer.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <map>

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// A drawer for layered networks
class LayeredNetworkTopologyDrawer : public AbstractNetworkTopologyDrawer
{
private:
public:
	LayeredNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method refreshes the drawing
	void refresh();
};

#endif