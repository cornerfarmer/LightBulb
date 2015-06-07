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

// This structure describes all options of an NeuralNetworkResultChart
struct AbstractNetworkTopologyDrawerOptions 
{
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

// A basic shape for an graphical component
class AbstractNetworkTopologyDrawer : public GraphicObject
{
private:	
	// This map will hold a circle shape for every neuron
	std::map<AbstractNeuron*, std::pair<sf::CircleShape, sf::Text>> neuronShapes;
	// This list will hold a line for every edge
	std::list<Arrow> edgeShapes;
	static const float angleDifferenceBetweenContraryEdges;

protected:
	std::unique_ptr<AbstractNetworkTopologyDrawerOptions> options;
	void addShapeFromNeuron(AbstractNeuron* neuron, sf::Vector2f position);
	void addEdgesToAllShapes();
public:
	AbstractNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);

};

#endif