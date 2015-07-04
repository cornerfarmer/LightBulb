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
	unsigned int xTimeStep;
	float xRangeEnd;
	float xRangeStart;
	unsigned int yInputNeuronIndex;
	unsigned int yTimeStep;
	float yRangeEnd;
	float yRangeStart;	
	unsigned int outputNeuronIndex;
	float ouputRangeStart;
	float ouputRangeEnd;
	int ouputTimeStep;

	NeuralNetworkResultChartOptions();	
	~NeuralNetworkResultChartOptions();
	NeuralNetworkResultChartOptions(const NeuralNetworkResultChartOptions &obj);

};

// A chart which visalizes the calculation of a neural network
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