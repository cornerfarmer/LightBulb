#pragma once

#ifndef _RBFNETWORKSTRUCTURECHART_H_
#define _RBFNETWORKSTRUCTURECHART_H_

// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <list>

// Forward declarations
class RBFNetwork;

// This structure describes all options of an RBFNetworkStructureChartOptions
struct RBFNetworkStructureChartOptions 
{
	int posX;
	int posY;
	// The height of the chart
	unsigned int height;
	// The width of the chart
	unsigned int width;
	// The selected rbfNetwork
	RBFNetwork* rbfNetwork;
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
	
	RBFNetworkStructureChartOptions()
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

		rbfNetwork = NULL;
	}
};

// A chart which shows the location of the rbf neurons inside a rbfNetwork
class RBFNetworkStructureChart : public GraphicObject
{
private:
	// A list of all circleShapes which represent the location of the clusters
	std::list<sf::CircleShape> rbfNeuronShapes;
	RBFNetworkStructureChartOptions options;
public:
	RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart and replaces all rbfNeuronShapes
	void recalculateAllValues();
};

#endif