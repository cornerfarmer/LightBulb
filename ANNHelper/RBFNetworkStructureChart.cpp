#include "RBFNetworkStructureChart.hpp"
#include "RBFNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "RBFThreshold.hpp"

RBFNetworkStructureChart::RBFNetworkStructureChart(int posX_, int posY_, RBFNetworkStructureChartOptions &options_)
	: GraphicObject(posX_, posY_)
{
	options = options_;
}

void RBFNetworkStructureChart::recalculateAllValues()
{
	// Clear the shape list
	rbfNeuronShapes.clear();
	// Go through all rbfNeurons in the rbfNetwork
	for (std::vector<AbstractNeuron*>::iterator neuron = options.rbfNetwork->getNeuronsInLayer(1)->begin(); neuron != options.rbfNetwork->getNeuronsInLayer(1)->end(); neuron++)
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
		newCircle.move(posX, posY);
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
	drawRect.setPosition(posX, posY);
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

