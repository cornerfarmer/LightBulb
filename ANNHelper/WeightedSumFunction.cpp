#include "WeightedSumFunction.hpp"
#include "Edge.hpp"
#include "AbstractNeuron.hpp"

float WeightedSumFunction::execute(std::vector<Edge*> &input, AbstractThreshold* threshold)
{
	float sum = 0.0;

	// Calculate the product of weight and output of every neuron and add it to the sum
	for (int i = 0; i < input.size(); i++)
	{
		sum += input[i]->getWeight() * input[i]->getPrevNeuron()->getActivation();
	}
	
	return sum;
}

AbstractInputFunction* WeightedSumFunction::getInputFunctionCopy()
{
	return new WeightedSumFunction(*this);
}
