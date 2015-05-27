#pragma once

#ifndef _NETWORKTOPOLOYDRAWEROPTIONS_H_
#define _NETWORKTOPOLOYDRAWEROPTIONS_H_

// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <map>

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// This structure describes all options of an NeuralNetworkResultChart
struct NetworkTopologyDrawerOptions 
{
	// Height of the drawing area
	unsigned int height;
	// Width of the drawing area
	unsigned int width;
	// The networkTopolohy
	AbstractNetworkTopology* networkTopology;
	
	NetworkTopologyDrawerOptions();	
};

// A basic shape for an graphical component
class NetworkTopologyDrawer : public GraphicObject
{
private:
	std::unique_ptr<NetworkTopologyDrawerOptions> options;
	// This map will hold a circle shape for every neuron
	std::map<AbstractNeuron*, sf::CircleShape> neuronShapes;
	// This list will hold a line for every edge
	std::list<sf::VertexArray> edgeShapes;
public:
	NetworkTopologyDrawer(int posX_, int posY_, NetworkTopologyDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method refreshes the drawing
	void refresh();
};

#endif