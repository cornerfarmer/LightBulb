// Includes
#include "Examples/NetworkSimulator.hpp"
#include "Examples/Network.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <iostream>

AbstractEvolutionObject* NetworkSimulator::createNewObject()
{
	return new Network(this);
}

NetworkSimulator::NetworkSimulator(bool enableGraphics_, std::vector<std::vector<float>> consumers_)
{
	consumers = consumers_;
	enableGraphics = enableGraphics_;
	if (enableGraphics)
	{
		window.create(sf::VideoMode(800, 700), "LightBulb!");
		NetworkDrawerOptions options;
		options.networkSimulator = this;
		options.startX = -1;
		options.endX = 5;
		options.startY = -2;
		options.endY = 2;

		drawer.reset(new NetworkDrawer(options));
	}
}

bool NetworkSimulator::doSimulationStep()
{
	for (auto position = objects.begin(); position != objects.end(); position++)
	{
		(*position)->doNNCalculation();
	}

	if (enableGraphics)
	{
		window.clear();
		drawer->recalculateAllValues();
		drawer->draw(window);
		window.display();
	}
	return false;
}

double NetworkSimulator::getScore(AbstractEvolutionObject* object)
{
	std::vector<std::vector<float>> pos = *static_cast<Network*>(object)->getPositions();

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

double NetworkSimulator::distanceBetweenPositions(std::vector<float>& pos1, std::vector<float>& pos2)
{
	double distance = 0;
	for (int c = 0; c < pos1.size(); c++)
	{
		distance += pow(pos1[c] - pos2[c], 2);
	}
	return sqrt(distance);
}

std::vector<std::vector<float>>* NetworkSimulator::getConsumers()
{
	return &consumers;
}
