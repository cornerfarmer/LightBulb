#include "RBFNetworkStructureChart.hpp"
#include "RBFNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "RBFThreshold.hpp"

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
	for (std::vector<StandardNeuron*>::iterator neuron = options.rbfNetwork->getNeurons()->front().begin(); neuron != options.rbfNetwork->getNeurons()->front().end(); neuron++)
	{
		// Create a new circle shape
		sf::CircleShape newCircle;
		// Extract the threshold of the current neuron
		RBFThreshold* thresholdOfNeuron = static_cast<RBFThreshold*>(static_cast<StandardNeuron*>(*neuron)->getThreshold());
		// Set the radius to the width of the neuron converted into the view range
		newCircle.setRadius(thresholdOfNeuron->getWidth() / (options.xRangeEnd - options.xRangeStart) * options.width);
		// Set the position to the wished coordinates of the neuron center converted into the view range
		newCircle.setPosition(((*thresholdOfNeuron->getCenterVector())[options.xRBFNeuronCenterCoordinateIndex] - options.xRangeStart) / (options.xRangeEnd - options.xRangeStart) * options.width, ((*thresholdOfNeuron->getCenterVector())[options.yRBFNeuronCenterCoordinateIndex] - options.yRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height);
		// Add the offset position of the chart
		newCircle.move(options.posX, options.posY);
		// Change the vertical scale depending of the view aspect ratio
		newCircle.setScale(1.0f, 1.0f / options.width * (options.xRangeEnd - options.xRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height);

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
	drawRect.setPosition(options.posX, options.posY);
	drawRect.setSize(sf::Vector2f(options.width, options.height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all neuron shapes
	for (std::list<sf::CircleShape>::iterator neuronShape = rbfNeuronShapes.begin(); neuronShape != rbfNeuronShapes.end(); neuronShape++)
	{	
		// Draw the circle shape
		window.draw(*neuronShape);
	}

}

