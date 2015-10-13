// Includes
#include "Examples/FunctionSimulator.hpp"
#include "Examples/Position.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <iostream>

AbstractEvolutionObject* FunctionSimulator::createNewObject()
{
	return new Position(this);
}

FunctionSimulator::FunctionSimulator()
{
	window.create(sf::VideoMode(800, 700), "LightBulb!");
	FunctionDrawerOptions options;
	options.functionSimulator = this;
	options.startX = -2.5;
	options.endX = 2.5;
	options.startY = -1.5;
	options.endY = 1.5;

//	options.startX = -0.5;
//	options.endX = 0.5;
//	options.startY = 0.25;
//	options.endY = 1.25;
	options.markedPositions.push_back(sf::Vector2f(0.0898f, -0.7126f));
	options.markedPositions.push_back(sf::Vector2f(-0.0898f, 0.7126f));
	drawer.reset(new FunctionDrawer(options));
}

void FunctionSimulator::doSimulationStep(EvolutionLearningRule& learningRule)
{
	for (auto position = objects.begin(); position != objects.end(); position++)
	{
		(*position)->doNNCalculation(learningRule);
	}

	window.clear();
	drawer->recalculateAllValues();
	drawer->draw(window);
	window.display();
}

double FunctionSimulator::getScore(AbstractEvolutionObject* object)
{
	std::vector<float> pos = static_cast<Position*>(object)->getPosition();
	return -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4));
}

