#include "Graphics\RBFNetworkStructureChart.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\RBFThreshold.hpp"

RBFNetworkStructureChart::RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_)
{
	options = options_;
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (options.rbfNetwork == NULL)
		throw std::invalid_argument("The given rbfNetwork is not valid");
	// Check if the indices are correct
	if (options.xRBFNeuronCenterCoordinateIndex >= options.rbfNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xRBFNeuronCenterCoordinateIndex'");
	if (options.yRBFNeuronCenterCoordinateIndex >= options.rbfNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yRBFNeuronCenterCoordinateIndex'");
}

void RBFNetworkStructureChart::recalculateAllValues()
{
	// Clear the shape list
	rbfNeuronShapes.clear();
	// Go through all rbfNeurons in the rbfNetwork
	for (auto neuron = options.rbfNetwork->getNeurons()->front().begin(); neuron != options.rbfNetwork->getNeurons()->front().end(); neuron++)
	{
		// Create a new circle shape
		sf::CircleShape newCircle;
		// Extract the threshold of the current neuron
		RBFThreshold* thresholdOfNeuron = static_cast<RBFThreshold*>(static_cast<StandardNeuron*>(*neuron)->getThreshold());
		// Set the radius to the width of the neuron converted into the view range
		newCircle.setRadius((float)(thresholdOfNeuron->getWidth() / (options.xRangeEnd - options.xRangeStart) * options.width));
		// Set the position to the wished coordinates of the neuron center converted into the view range
		newCircle.setPosition((float)(((*thresholdOfNeuron->getCenterVector())[options.xRBFNeuronCenterCoordinateIndex] - options.xRangeStart) / (options.xRangeEnd - options.xRangeStart) * options.width), (float)(((*thresholdOfNeuron->getCenterVector())[options.yRBFNeuronCenterCoordinateIndex] - options.yRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height));
		// Add the offset position of the chart
		newCircle.move((float)options.posX, (float)options.posY);
		// Change the vertical scale depending of the view aspect ratio
		newCircle.setScale(1.0f, (float)(1.0f / options.width * (options.xRangeEnd - options.xRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height));

		// Set the style of the circle shape
		newCircle.setFillColor(sf::Color::Transparent);
		newCircle.setOutlineColor(sf::Color::White);
		newCircle.setOutlineThickness(1);
		newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
		newCircle.setPointCount(100);

		// Add the circle shape to the list
		rbfNeuronShapes.push_back(newCircle);
	}
}

void RBFNetworkStructureChart::draw(sf::RenderWindow &window)
{	
	// Outline the part of the window which will contain our chart
	sf::RectangleShape drawRect;
	drawRect.setPosition((float)options.posX, (float)options.posY);
	drawRect.setSize(sf::Vector2f((float)options.width, (float)options.height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all neuron shapes
	for (auto neuronShape = rbfNeuronShapes.begin(); neuronShape != rbfNeuronShapes.end(); neuronShape++)
	{	
		// Draw the circle shape
		window.draw(*neuronShape);
	}

}

