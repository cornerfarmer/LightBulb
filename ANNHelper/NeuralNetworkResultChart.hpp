#pragma once

#ifndef _NUERALNETWORKRESULTCHART_H_
#define _NUERALNETWORKRESULTCHART_H_

// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>

// Forward declarations
class NeuralNetwork;
class ActivationOrder;

// This structure describes all options of an NeuralNetworkResultChart
struct NeuralNetworkResultChartOptions 
{
	bool binaryInterpretation;
	unsigned int height;
	unsigned int width;
	NeuralNetwork* neuralNetwork;
	ActivationOrder* activationOrder;	
	unsigned int xInputNeuronIndex;
	float xRangeEnd;
	float xRangeStart;
	unsigned int yInputNeuronIndex;
	float yRangeEnd;
	float yRangeStart;	
	unsigned int outputNeuronIndex;
	float ouputRangeStart;
	float ouputRangeEnd;
	NeuralNetworkResultChartOptions()
	{
		binaryInterpretation = true;
		height = 300;
		width = 300;
		neuralNetwork = NULL;
		xInputNeuronIndex = 0;
		xRangeStart = 0;
		xRangeEnd = 1;
		yInputNeuronIndex = 1;
		yRangeStart = 0;
		yRangeEnd = 1;
		activationOrder = NULL;
		outputNeuronIndex = 0;
		ouputRangeStart = 0;
		ouputRangeEnd = 1;
	}

	~NeuralNetworkResultChartOptions()
	{
		delete(activationOrder);
	}
};

// A basic shape for an graphical component
class NeuralNetworkResultChart : public GraphicObject
{
private:
	NeuralNetworkResultChartOptions* options;
	// This texture will contain the chart, calculated in recalculateAllValues
	sf::Texture texture;
public:
	~NeuralNetworkResultChart();
	NeuralNetworkResultChart(int posX_, int posY_, NeuralNetworkResultChartOptions* options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif