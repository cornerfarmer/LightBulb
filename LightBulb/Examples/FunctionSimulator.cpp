// Includes
#include "Examples\FunctionSimulator.hpp"
#include "Examples\Position.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
//Library includes
#include <iostream>

AbstractEvolutionObject* FunctionSimulator::createNewObject()
{
	return new Position(this);
}

FunctionSimulator::FunctionSimulator()
{
	
}

void FunctionSimulator::doSimulationStep(EvolutionLearningRule& learningRule)
{	
	for (auto position = objects.begin(); position != objects.end(); position++)
	{
		(*position)->doNNCalculation(learningRule);
	}
}

double FunctionSimulator::getScore(AbstractEvolutionObject* object)
{
	std::vector<float> pos = static_cast<Position*>(object)->getPosition();
	return -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4));
}

