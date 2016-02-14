// Includes
#include "Examples/Position.hpp"
#include "Examples/FunctionSimulator.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"

Position::Position(FunctionSimulator* functionSimulator_)
	: AbstractSimpleEvolutionObject(functionSimulator_, 1, 2)
{
	functionSimulator = functionSimulator_;
	position.resize(2);
}

void Position::getNNInput(std::vector<double>& input)
{
	input.resize(1);
	input[0] = 1;
}

void Position::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 2; i++)
	{	
		position[i] = output[i];
	}
}

std::vector<float> Position::getPosition()
{
	return position;
}

Position::~Position()
{
}

