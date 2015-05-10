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
	unsigned int height;
	unsigned int width;
	RBFNetwork* rbfNetwork;

	float xRangeEnd;
	float xRangeStart;
	unsigned int xRBFNeuronCenterCoordinateIndex;
	float yRangeEnd;
	float yRangeStart;	
	unsigned int yRBFNeuronCenterCoordinateIndex;

	RBFNetworkStructureChartOptions()
	{
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

// A basic shape for an graphical component
class RBFNetworkStructureChart : public GraphicObject
{
private:
	// This texture will contain the chart, calculated in recalculateAllValues
	std::list<sf::CircleShape> rbfNeuronShapes;
	RBFNetworkStructureChartOptions options;
public:
	RBFNetworkStructureChart(int posX_, int posY_, RBFNetworkStructureChartOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif