// Includes
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "Examples/NetworkEvolution/Network.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
//Library includes
#include <iostream>

using namespace LightBulb;

AbstractIndividual* NetworkSimulator::createNewIndividual()
{
	return new Network(*this);
}

NetworkSimulator::NetworkSimulator(std::vector<std::vector<float>> consumers_)
{
	consumers = consumers_;
	/*if (enableGraphics)
	{
		window.create(sf::VideoMode(800, 700), "LightBulb!");
		NetworkDrawerOptions options;
		options.networkSimulator = this;
		options.startX = -1;
		options.endX = 5;
		options.startY = -2;
		options.endY = 2;

		drawer.reset(new NetworkDrawer(options));
	}*/
}

void NetworkSimulator::doSimulationStep()
{
	for (auto position = individuals.begin(); position != individuals.end(); position++)
	{
		(*position)->doNNCalculation();
	}

	/*if (enableGraphics)
	{
		window.clear();
		drawer->recalculateAllValues();
		drawer->draw(window);
		window.display();
	}*/
}

double NetworkSimulator::getFitness(const AbstractIndividual& individual) const
{
	std::vector<std::vector<float>> pos = static_cast<const Network&>(individual).getPositions();

	double length = 0;
	for (int p = 0; p < pos.size(); p++)
	{
		length += distanceBetweenPositions(pos[p], consumers[p * 2]);
		length += distanceBetweenPositions(pos[p], consumers[p * 2 + 1]);
		if (p < pos.size() - 1)
			length += distanceBetweenPositions(pos[p], pos[p + 1]);
	}

	return -length;
}

double NetworkSimulator::distanceBetweenPositions(const std::vector<float>& pos1, const std::vector<float>& pos2) const
{
	double distance = 0;
	for (int c = 0; c < pos1.size(); c++)
	{
		distance += pow(pos1[c] - pos2[c], 2);
	}
	return sqrt(distance);
}

std::vector<std::vector<float>>& NetworkSimulator::getConsumers()
{
	return consumers;
}
