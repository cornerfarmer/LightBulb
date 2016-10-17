// Includes
#include "Examples/SimpleReinforcement/SimpleReinforcementWorld.hpp"
#include <Learning/LearningState.hpp>

//Library includes

using namespace LightBulb;

SimpleReinforcementWorld::SimpleReinforcementWorld(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementWorld(options_, epsilonGreedly, epsilon)
{
	posX = 0;
	posY = 0;
}

double SimpleReinforcementWorld::doSimulationStep()
{
	if ((posX == 0 && posY == 0) || (posX == 3 && posY == 3))
	{
		posX = 1;
		posY = 2;
	}

	doNNCalculation();

	return -1;
}

void SimpleReinforcementWorld::getNNInput(std::vector<double>& input)
{
	input.resize(4);
	if (posX == 0)
	{
		input[0] = 0;
		input[1] = 0;
	}
	else if (posX == 1)
	{
		input[0] = 0;
		input[1] = 1;
	}
	else if (posX == 2)
	{
		input[0] = 1;
		input[1] = 0;
	}
	else if (posX == 3)
	{
		input[0] = 1;
		input[1] = 1;
	}
	
	if (posY == 0)
	{
		input[2] = 0;
		input[3] = 0;
	}
	else if (posY == 1)
	{
		input[2] = 0;
		input[3] = 1;
	}
	else if (posY == 2)
	{
		input[2] = 1;
		input[3] = 0;
	}
	else if (posY == 3)
	{
		input[2] = 1;
		input[3] = 1;
	}
}

void SimpleReinforcementWorld::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0])
		posX -= 1;
	else if(output[1])
		posX += 1;
	else if (output[2])
		posY -= 1;
	else if (output[3])
		posY += 1;

	posX = std::max(0, std::min(3, posX));
	posY = std::max(0, std::min(3, posY));
}


std::vector<std::string> SimpleReinforcementWorld::getDataSetLabels() const
{
	auto labels = AbstractReinforcementWorld::getDataSetLabels();
	return labels;
}

bool SimpleReinforcementWorld::isTerminalState()
{
	return ((posX == 0 && posY == 0) || (posX == 3 && posY == 3));
}
