#pragma once

#ifndef _LVQNETWORKSTRUCTURECHART_H_
#define _LVQNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <list>

// Forward declarations
class LVQNetwork;

// This structure describes all options of an RBFNetworkStructureChartOptions
struct LVQNetworkStructureChartOptions 
{
	int posX;
	int posY;
	// The height of the chart
	unsigned int height;
	// The width of the chart
	unsigned int width;
	// The selected lvqNetwork
	LVQNetwork* lvqNetwork;
	// The end of the displayed range in x-direction
    float xRangeEnd;
	// The start of the displayed range in x-direction
    float xRangeStart;
	// The index of the coordinate in the center vector displayed in x-direction
	unsigned int xRBFNeuronCenterCoordinateIndex;
	// The end of the displayed range in y-direction
    float yRangeEnd;
	// The start of the displayed range in y-direction
    float yRangeStart;    
	// The index of the coordinate in the center vector displayed in y-direction
	unsigned int yRBFNeuronCenterCoordinateIndex;
	
	LVQNetworkStructureChartOptions()
	{
		posX = 0;
		posY = 0;
		// Set all options to default values
		xRangeStart = 0;
		xRangeEnd = 1;
		xRBFNeuronCenterCoordinateIndex = 0;

		yRangeStart = 0;
		yRangeEnd = 1;
		yRBFNeuronCenterCoordinateIndex = 1;
		
		height = 300;
		width = 300;

		lvqNetwork = NULL;
	}
};

// A chart which shows the location of the rbf neurons inside a rbfNetwork
class LVQNetworkStructureChart : public GraphicObject
{
private:
	// A list of all circleShapes which represent the location of the clusters
	std::list<sf::CircleShape> rbfNeuronShapes;
	LVQNetworkStructureChartOptions options;
public:
	LVQNetworkStructureChart(LVQNetworkStructureChartOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart and replaces all rbfNeuronShapes
	void recalculateAllValues();
};

#endif
