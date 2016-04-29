// Includes
#include "Examples/NetworkDrawer.hpp"
#include "Examples/NetworkSimulator.hpp"
#include "Examples/Network.hpp"
// Library includes
#include <exception>
#include <vector>

NetworkDrawer::NetworkDrawer(NetworkDrawerOptions& options_)
{
	options.reset(new NetworkDrawerOptions(options_));

	// Check if all given options are correct
	// Check if the given nature is valid
	if (options->networkSimulator == NULL)
		throw std::invalid_argument("The given networkSimulator is not valid");
}

void NetworkDrawer::recalculateAllValues()
{
	connections = sf::VertexArray(sf::Lines, 22);
	mutationStrengths.resize(options->networkSimulator->getPopulationSize());
	consumerShapes.resize(options->networkSimulator->getConsumers()->size());
	Network* network = static_cast<Network*>(options->networkSimulator->getEvolutionObjects()->front());

	auto consumerShape = consumerShapes.begin();
	for (auto consumer = options->networkSimulator->getConsumers()->begin(); consumer != options->networkSimulator->getConsumers()->end(); consumer++, consumerShape++)
	{
		sf::Vector2f graphicsPosition(((*consumer)[0] - options->startX) / (options->endX - options->startX) * options->width - 1, ((*consumer)[1] - options->startY) / (options->endY - options->startY) * options->height - 1);
		consumerShape->setPosition(graphicsPosition);
		consumerShape->setSize(sf::Vector2f(2, 2));
		consumerShape->setFillColor(sf::Color::White);
	}

	auto mutationStrength = mutationStrengths.begin();
	std::vector<double> objectMutationStrengths = *network->getMutationStrength();
	std::vector<std::vector<float>> objectPositions = *network->getPositions();
	int connectionsIndex = 0;
	for (int p = 0; p < network->getPositions()->size(); p++, mutationStrength++)
	{
		sf::Vector2f graphicsPosition((objectPositions[p][0] - options->startX) / (options->endX - options->startX) * options->width - 1, (objectPositions[p][1] - options->startY) / (options->endY - options->startY) * options->height - 1);

		if (p > 0)
		{
			connections[connectionsIndex++].position = graphicsPosition;
			connections[connectionsIndex++].position = connections[connectionsIndex - 4].position;
		}

		connections[connectionsIndex++].position = graphicsPosition;
		connections[connectionsIndex++].position = consumerShapes[p * 2].getPosition();

		connections[connectionsIndex++].position = graphicsPosition;
		connections[connectionsIndex++].position = consumerShapes[p * 2 + 1].getPosition();


		mutationStrength->setPosition(graphicsPosition);
		mutationStrength->setRadius(1);
		mutationStrength->setScale(objectMutationStrengths[p * 2] / (options->startX - options->endX) * options->width, objectMutationStrengths[p * 2 + 1] / (options->startY - options->endY) * options->height);

		mutationStrength->setFillColor(sf::Color::Transparent);
		mutationStrength->setOutlineColor(sf::Color::White);
		mutationStrength->setOutlineThickness(0.1);
		mutationStrength->setOrigin(mutationStrength->getRadius(), mutationStrength->getRadius());
		mutationStrength->setPointCount(100);
	}

	
}

void NetworkDrawer::draw(sf::RenderWindow &window)
{
	// Outline the part of the window which will contain our chart
	sf::RectangleShape drawRect;
	drawRect.setPosition((float)options->posX, (float)options->posY);
	drawRect.setSize(sf::Vector2f((float)options->width, (float)options->height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all rectangles and draw them
	for (auto consumerShape = consumerShapes.begin(); consumerShape != consumerShapes.end(); consumerShape++)
	{
		window.draw(*consumerShape);
	}

	for (auto mutationStrength = mutationStrengths.begin(); mutationStrength != mutationStrengths.end(); mutationStrength++)
	{
		window.draw(*mutationStrength);
	}

	window.draw(connections);
}

