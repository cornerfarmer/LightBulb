// Includes
#include "Function/WeightedSumFunction.hpp"
#include "Neuron/Edge.hpp"
#include "Neuron/AbstractNeuron.hpp"

double WeightedSumFunction::execute(std::list<Edge*> &input, AbstractThreshold* threshold, double additionalInput, std::map<AbstractNeuron*, double>* neuronOutputCache)
{
	double sum = additionalInput;

	// Calculate the product of weight and output of every neuron and add it to the sum
	for (auto edge = input.begin(); edge != input.end(); edge++)
	{
		// Use the neuronOutputCache if possible else use the current activation
		sum += (*edge)->getWeight() * (neuronOutputCache == NULL || neuronOutputCache->find((*edge)->getPrevNeuron()) == neuronOutputCache->end() ? (*edge)->getPrevNeuron()->getActivation() : (*neuronOutputCache)[(*edge)->getPrevNeuron()]);
	}

	return sum;
}

AbstractInputFunction* WeightedSumFunction::getInputFunctionCopy()
{
	return new WeightedSumFunction(*this);
}
