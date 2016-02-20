// Includes
#include "Graphics/AbstractNetworkStructureChart.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/RBFThreshold.hpp"

AbstractNetworkStructureChart::AbstractNetworkStructureChart(AbstractNetworkStructureChartOptions* options_)
{
	options = options_;
}

void AbstractNetworkStructureChart::recalculateAllValues()
{
	// Clear the shape list
	neuronShapes.clear();
	// Go through all neurons
	for (auto neuron = getNeurons()->begin(); neuron != getNeurons()->end(); neuron++)
	{
		// Create a new circle shape
		sf::CircleShape newCircle;
		// Extract the radius and position of the current neuron
		double radius = getRadiusOfNeuron(**neuron);
		std::vector<double> positionVector = getPositionOfNeuron(**neuron);
		// Set the radius to the width of the neuron converted into the view range
		newCircle.setRadius((float)(radius / (options->xRangeEnd - options->xRangeStart) * options->width));
		// Set the position to the wished coordinates of the neuron center converted into the view range
		newCircle.setPosition((float)((positionVector[options->xNeuronCoordinateIndex] - options->xRangeStart) / (options->xRangeEnd - options->xRangeStart) * options->width), (float)((positionVector[options->yNeuronCoordinateIndex] - options->yRangeStart) / (options->yRangeEnd - options->yRangeStart) * options->height));
		// Add the offset position of the chart
		newCircle.move((float)options->posX, (float)options->posY);
		// Change the vertical scale depending of the view aspect ratio
		newCircle.setScale(1.0f, (float)(1.0f / options->width * (options->xRangeEnd - options->xRangeStart) / (options->yRangeEnd - options->yRangeStart) * options->height));

		// Set the style of the circle shape
		newCircle.setFillColor(sf::Color::Transparent);
		newCircle.setOutlineColor(sf::Color::White);
		newCircle.setOutlineThickness(1);
		newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
		newCircle.setPointCount(100);

		// Add the circle shape to the list
		neuronShapes[*neuron] = newCircle;
	}
}

void AbstractNetworkStructureChart::draw(sf::RenderWindow &window)
{	
	// Outline the part of the window which will contain our chart
	sf::RectangleShape drawRect;
	drawRect.setPosition((float)options->posX, (float)options->posY);
	drawRect.setSize(sf::Vector2f((float)options->width, (float)options->height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all neuron shapes
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{	
		// Draw the circle shape
		window.draw(neuronShape->second);
	}

}

