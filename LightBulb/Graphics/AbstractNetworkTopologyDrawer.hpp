#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOYDRAWEROPTIONS_H_
#define _ABSTRACTNETWORKTOPOLOYDRAWEROPTIONS_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include "Graphics\Arrow.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"

// Library includes
#include <map>

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;
class AbstractNeuron;
class Edge;

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
	// The network
	NeuralNetwork* network;
	
	AbstractNetworkTopologyDrawerOptions();	
};

// A basic shape for an NetworkTopologyDrawer
class AbstractNetworkTopologyDrawer : public GraphicObject
{
private:
	// This map will hold a circle shape for every neuron
	std::map<AbstractNeuron*, std::pair<sf::CircleShape, sf::Text>> neuronShapes;
	// This list will hold a line for every edge
	std::map<Edge*, std::unique_ptr<Arrow>> edgeShapes;
	// This constant value holds the angle difference beetween an incoming and an outcoming edge
    static const float angleDifferenceBetweenContraryEdges;
	// Constants which hold the color values of the neuronShapes
	static const sf::Color fillColorStandardNeuron;
	static const sf::Color fillColorInputNeuron;
	static const sf::Color fillColorActivatedNeuron;
	static const sf::Color outlineColorStandardNeuron;
	static const sf::Color outlineColorOutputNeuron;
protected:
	std::unique_ptr<AbstractNetworkTopologyDrawerOptions> options;

	NeuralNetworkIO<double>* currentCalculationInput;
	AbstractActivationOrder* currentCalculationActivationOrder;
	int currentTimeStep;
	// Add a shape with the given position 
	void addShapeFromNeuron(AbstractNeuron* neuron, sf::Vector2f position);
	// Adds edgeShapes for all edges between all neuronShapes
	void addEdgesToAllShapes();
public:
	AbstractNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions &options_);
	// This method draws the network topology
	void draw(sf::RenderWindow &window);

	void startNewCalculation(NeuralNetworkIO<double>& input, AbstractActivationOrder &activationOrder);

	void nextCalculationStep();

	void resetCalculation();

	void refreshAllValues();

	void refreshAllActivations();
};

#endif
