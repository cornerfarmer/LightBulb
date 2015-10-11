// Includes
#include "Function/EuclideanDistance.hpp"
#include "Neuron/Edge.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/RBFThreshold.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

double EuclideanDistance::execute(std::list<Edge*> &input, AbstractThreshold* threshold, double additionalInput, std::map<AbstractNeuron*, double>* neuronOutputCache)
{
	double euclideanDistance = 0.0;

	// Calculate the square of the distance between the output and the center
	for (auto edge = input.begin(); edge != input.end(); edge++)
	{
		euclideanDistance += pow((neuronOutputCache == NULL ? (*edge)->getPrevNeuron()->getActivation() : (*neuronOutputCache)[(*edge)->getPrevNeuron()]) - (*edge)->getWeight(), 2);
	}

	// Sqrt
	euclideanDistance = sqrt(euclideanDistance);
	
	return euclideanDistance;
}

AbstractInputFunction* EuclideanDistance::getInputFunctionCopy()
{
	return new EuclideanDistance(*this);
}
