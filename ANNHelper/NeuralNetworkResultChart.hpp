#pragma once

#ifndef _NUERALNETWORKRESULTCHART_H_
#define _NUERALNETWORKRESULTCHART_H_

// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;

// This structure describes all options of an NeuralNetworkResultChart
struct NeuralNetworkResultChartOptions 
{
	int posX;
	int posY;
	bool binaryInterpretation;
	unsigned int height;
	unsigned int width;
	NeuralNetwork* neuralNetwork;
	AbstractActivationOrder* activationOrder;	
	unsigned int xInputNeuronIndex;
	float xRangeEnd;
	float xRangeStart;
	unsigned int yInputNeuronIndex;
	float yRangeEnd;
	float yRangeStart;	
	unsigned int outputNeuronIndex;
	float ouputRangeStart;
	float ouputRangeEnd;

	NeuralNetworkResultChartOptions();	
	~NeuralNetworkResultChartOptions();
	NeuralNetworkResultChartOptions(const NeuralNetworkResultChartOptions &obj);

};

// A basic shape for an graphical component
class NeuralNetworkResultChart : public GraphicObject
{
private:
	std::unique_ptr<NeuralNetworkResultChartOptions> options;
	// This texture will contain the chart, calculated in recalculateAllValues
	sf::Texture texture;
public:
	NeuralNetworkResultChart(NeuralNetworkResultChartOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif