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

// A basic shape for an graphical component
class LayeredNetworkTopologyDrawer : public AbstractNetworkTopologyDrawer
{
private:
public:
	LayeredNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method refreshes the drawing
	void refresh();
};

#endif