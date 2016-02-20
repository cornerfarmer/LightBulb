#pragma once

#ifndef _NUERALNETWORKRESULTCHART_H_
#define _NUERALNETWORKRESULTCHART_H_

// Includes
#include "Graphics/GraphicObject.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <memory>

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;

// This structure describes all options of an NeuralNetworkResultChart
struct NeuralNetworkResultChartOptions 
{
	// Position
	int posX;
	int posY;
	// Dont print grey output only black and white
	bool binaryInterpretation;
	// Size
	unsigned int height;
	unsigned int width;
	// Network
	NeuralNetwork* neuralNetwork;
	AbstractActivationOrder* activationOrder;	
	// x-Axis
	unsigned int xInputNeuronIndex;
	unsigned int xTimeStep;
    float xRangeEnd;
    float xRangeStart;
	// y-Axis
	unsigned int yInputNeuronIndex;
	unsigned int yTimeStep;
    float yRangeEnd;
    float yRangeStart;    
	// output
	unsigned int outputNeuronIndex;
    float ouputRangeStart;
    float ouputRangeEnd;
	int ouputTimeStep;

	NeuralNetworkResultChartOptions();	
	~NeuralNetworkResultChartOptions();
	NeuralNetworkResultChartOptions(const NeuralNetworkResultChartOptions &obj);

};

// A chart which visualizes the calculation of a neural network
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
