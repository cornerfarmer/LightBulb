#include "WeightedSumFunction.hpp"
#include "Edge.hpp"
#include "Neuron.hpp"

float WeightedSumFunction::execute(std::list<Edge*> input)
{
	float sum = 0.0;

	// Calculate the product of weight and output of every neuron and add it to the sum
	for (std::list<Edge*>::iterator edge = input.begin(); edge != input.end(); edge++)
	{
		sum += (*edge)->getWeight() * (*edge)->getPrevNeuron()->getActivation();
	}
	
	return sum;
}
