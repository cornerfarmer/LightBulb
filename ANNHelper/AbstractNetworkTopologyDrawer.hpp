#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOYDRAWEROPTIONS_H_
#define _ABSTRACTNETWORKTOPOLOYDRAWEROPTIONS_H_


// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <map>
#include "Arrow.hpp"

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// This structure describes all options of an AbstractNetworkTopologyDrawer
struct AbstractNetworkTopologyDrawerOptions 
{
	// Position of the drawing area
	int posX;
	int posY;
	// Height of the drawing area
	unsigned int height;
	// Width of the drawing area
	unsigned int width;
	// The networkTopolohy
	AbstractNetworkTopology* networkTopology;
	
	AbstractNetworkTopologyDrawerOptions();	
};

// A basic shape for an NetworkTopologyDrawer
class AbstractNetworkTopologyDrawer : public GraphicObject
{
private:	
	// This map will hold a circle shape for every neuron
	std::map<AbstractNeuron*, std::pair<sf::CircleShape, sf::Text>> neuronShapes;
	// This list will hold a line for every edge
	std::list<Arrow> edgeShapes;
	// This constant value holds the angle difference beetween an incoming and an outcoming edge
	static const float angleDifferenceBetweenContraryEdges;
protected:
	std::unique_ptr<AbstractNetworkTopologyDrawerOptions> options;
	// Add a shape with the given position 
	void addShapeFromNeuron(AbstractNeuron* neuron, sf::Vector2f position);
	// Adds edgeShapes for all edges between all neuronShapes
	void addEdgesToAllShapes();
public:
	AbstractNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method draws the network topology
	void draw(sf::RenderWindow &window);

};

#endif