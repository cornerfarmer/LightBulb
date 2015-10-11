#pragma once

#ifndef _ABSTRACTNETWORKSTRUCTURECHART_H_
#define _ABSTRACTNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics/GraphicObject.hpp"
#include <SFML/Graphics.hpp>
#include <list>

// Forward declarations
class StandardNeuron;

// This structure describes all options of an RBFNetworkStructureChartOptions
struct AbstractNetworkStructureChartOptions 
{
	int posX;
	int posY;
	// The height of the chart
	unsigned int height;
	// The width of the chart
	unsigned int width;
	// The end of the displayed range in x-direction
    float xRangeEnd;
	// The start of the displayed range in x-direction
    float xRangeStart;
	// The index of the coordinate in the center vector displayed in x-direction
	unsigned int xNeuronCoordinateIndex;
	// The end of the displayed range in y-direction
    float yRangeEnd;
	// The start of the displayed range in y-direction
    float yRangeStart;    
	// The index of the coordinate in the center vector displayed in y-direction
	unsigned int yNeuronCoordinateIndex;
	
	AbstractNetworkStructureChartOptions()
	{
		posX = 0;
		posY = 0;
		// Set all options to default values
		xRangeStart = 0;
		xRangeEnd = 1;
		xNeuronCoordinateIndex = 0;

		yRangeStart = 0;
		yRangeEnd = 1;
		yNeuronCoordinateIndex = 1;
		
		height = 300;
		width = 300;
	}
};

// A chart which shows the location of neurons
class AbstractNetworkStructureChart : public GraphicObject
{
protected:
	// A list of all circleShapes which represent the location of the neurons
	std::map<StandardNeuron*, sf::CircleShape> neuronShapes;	
	// Holds all options
	AbstractNetworkStructureChartOptions* options;
	// This method should return all relevant neurons
	virtual std::vector<StandardNeuron*>* getNeurons() = 0;
	// This method should return the radius of a neuron in the chart
	virtual double getRadiusOfNeuron(StandardNeuron& neuron) = 0;
	// This method should return the position of a neuron
	virtual std::vector<double> getPositionOfNeuron(StandardNeuron& neuron) = 0;
public:
	AbstractNetworkStructureChart(AbstractNetworkStructureChartOptions* options_);
	// This method draws the calculated chart
	virtual void draw(sf::RenderWindow &window);
	// This method recalculates the chart and replaces all neuronShapes
	virtual void recalculateAllValues();
};

#endif
