// Includes
#include "Examples/Position.hpp"
#include "Examples/FunctionSimulator.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"

Position::Position(FunctionSimulator* functionSimulator_)
	: AbstractSimpleEvolutionObject(functionSimulator_, 1, 2, false)
{
	functionSimulator = functionSimulator_;
	position.resize(2);
}

NeuralNetworkIO<double> Position::getNNInput()
{
	NeuralNetworkIO<double> input(1);	
	input.set(0, 0, 1);	
	return input;
}

void Position::interpretNNOutput(NeuralNetworkIO<double>* output)
{
	for (int i = 0; i < 2; i++)
	{	
		position[i] = output->get(0, i);
	}
}

std::vector<float> Position::getPosition()
{
	return position;
}

Position::~Position()
{
}

