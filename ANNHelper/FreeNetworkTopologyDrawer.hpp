#pragma once

#ifndef _FREENETWORKTOPOLOYDRAWEROPTIONS_H_
#define _FREENETWORKTOPOLOYDRAWEROPTIONS_H_

// Includes
#include "AbstractNetworkTopologyDrawer.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <map>

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// Drawer for FreeNetworkTopologies
class FreeNetworkTopologyDrawer : public AbstractNetworkTopologyDrawer
{
private:
public:
	FreeNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method refreshes the drawing
	void refresh();
};

#endif