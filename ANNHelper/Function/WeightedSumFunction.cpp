#include "Function\WeightedSumFunction.hpp"
#include "Neuron\Edge.hpp"
#include "Neuron\AbstractNeuron.hpp"

float WeightedSumFunction::execute(std::list<Edge*> &input, AbstractThreshold* threshold, float additionalInput, std::map<AbstractNeuron*, float>* neuronOutputCache)
{
	float sum = additionalInput;

	// Calculate the product of weight and output of every neuron and add it to the sum
	for (std::list<Edge*>::iterator edge = input.begin(); edge != input.end(); edge++)
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
