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
	rbfNeuronShapes.clear();
	for (std::vector<AbstractNeuron*>::iterator neuron = options.rbfNetwork->getNeuronsInLayer(1)->begin(); neuron != options.rbfNetwork->getNeuronsInLayer(1)->end(); neuron++)
	{
		sf::CircleShape newCircle;
		RBFThreshold* thresholdOfNeuron = static_cast<RBFThreshold*>(static_cast<StandardNeuron*>(*neuron)->getThreshold());
		newCircle.setRadius(thresholdOfNeuron->getWidth() / (options.xRangeEnd - options.xRangeStart) * options.width);
		newCircle.setPosition(((*thresholdOfNeuron->getCenterVector())[options.xRBFNeuronCenterCoordinateIndex] - options.xRangeStart) / (options.xRangeEnd - options.xRangeStart) * options.width, ((*thresholdOfNeuron->getCenterVector())[options.yRBFNeuronCenterCoordinateIndex] - options.yRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height);
		newCircle.setScale(1.0f, 1.0f / options.width * (options.xRangeEnd - options.xRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height);

		newCircle.setFillColor(sf::Color::Transparent);
		newCircle.setOutlineColor(sf::Color::White);
		newCircle.setOutlineThickness(1);
		newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius() );
		newCircle.setPointCount(100);
		rbfNeuronShapes.push_back(newCircle);
	}
}

void RBFNetworkStructureChart::draw(sf::RenderWindow &window)
{	sf::RectangleShape drawRect;

	drawRect.setPosition(posX, posY);
	drawRect.setSize(sf::Vector2f(options.width, options.height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	for (std::list<sf::CircleShape>::iterator neuronShape = rbfNeuronShapes.begin(); neuronShape != rbfNeuronShapes.end(); neuronShape++)
	{	
		(*neuronShape).move(posX, posY);
		window.draw(*neuronShape);
		(*neuronShape).move(-posX, -posY);
	}

}

