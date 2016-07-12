// Includes
#include "Examples/SimpleReinforcement/SimpleReinforcementWorld.hpp"
#include <Learning/LearningState.hpp>

//Library includes

SimpleReinforcementWorld::SimpleReinforcementWorld(LayeredNetworkOptions& options_)
	: AbstractReinforcementWorld(options_)
{
	round = 0;
}

double SimpleReinforcementWorld::doSimulationStep()
{
	doNNCalculation();

	return rating;
}

void SimpleReinforcementWorld::getNNInput(std::vector<double>& input)
{
	input.resize(2);
	if (round == 0)
	{
		input[0] = 0;
		input[1] = 0;
	}
	else if (round == 1)
	{
		input[0] = 0;
		input[1] = 1;
	}
	else if (round == 2)
	{
		input[0] = 1;
		input[1] = 0;
	}
	else if (round == 3)
	{
		input[0] = 1;
		input[1] = 1;
	}
	round = (round + 1) % 4;
	
	expectedOutput = (input[0] && !input[1]) || (!input[0] && input[1]);
}

void SimpleReinforcementWorld::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0] == expectedOutput)
		rating = 1;
	else
		rating = -1;
}


std::vector<std::string> SimpleReinforcementWorld::getDataSetLabels()
{
	auto labels = AbstractReinforcementWorld::getDataSetLabels();
	return labels;
}
