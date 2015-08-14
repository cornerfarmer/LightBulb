#pragma once

#ifndef _SOMMAPPINGCHART_H_
#define _SOMMAPPINGCHART_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>
#include <map>

// Forward declarations
class SOMNetwork;
class StandardNeuron;

// This structure describes all options of an NeuralNetworkResultChart
struct SOMMappingChartOptions 
{
	// Position
	int posX;
	int posY;
	// Zoom
	float scalingX;
	float scalingY;
	// Network
	SOMNetwork* somNetwork;
	// Red part of the output
	unsigned int rInputNeuronIndex;
    float rRangeEnd;
    float rRangeStart;
	// Green part of the output
	unsigned int gInputNeuronIndex;
    float gRangeEnd;
    float gRangeStart;    
	// Blue part of the output
	unsigned int bInputNeuronIndex;
    float bRangeEnd;
    float bRangeStart;   

	SOMMappingChartOptions()
	{
		posX = 0;
		posY = 0;
		scalingX = 10;
		scalingY = 10;
		somNetwork = NULL;
		rInputNeuronIndex = 0;
		rRangeStart = 0;
		rRangeEnd = 255;
		gInputNeuronIndex = 1;
		gRangeStart = 0;
		gRangeEnd = 255;
		bInputNeuronIndex = 2;
		bRangeStart = 0;
		bRangeEnd = 255;
	}
};

// A chart which visualizes the output of a som
class SOMMappingChart : public GraphicObject
{
private:
	std::unique_ptr<SOMMappingChartOptions> options;
	// This texture will contain the chart, calculated in recalculateAllValues
	std::map<StandardNeuron*, sf::RectangleShape> rectangles;
public:
	SOMMappingChart(SOMMappingChartOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif
