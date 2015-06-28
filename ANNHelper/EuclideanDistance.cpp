#include "EuclideanDistance.hpp"
#include "Edge.hpp"
#include "AbstractNeuron.hpp"
#include "RBFThreshold.hpp"
#include <stdexcept>

float EuclideanDistance::execute(std::list<Edge*> &input, AbstractThreshold* threshold, float additionalInput, std::map<AbstractNeuron*, float>* neuronOutputCache)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);

	// Make sure the given threshold is a RBFThreshold
	if (!rbfThreshold)
		std::invalid_argument("The threshold has to be a RBFThreshold");

	float euclideanDistance = 0.0;

	// Calculate the square of the distance between the output and the center
	std::vector<float>::iterator centerCoordinate = (*rbfThreshold->getCenterVector()).begin();
	for (std::list<Edge*>::iterator edge = input.begin(); edge != input.end(); edge++, centerCoordinate++)
	{
		euclideanDistance += pow((neuronOutputCache == NULL ? (*edge)->getPrevNeuron()->getActivation() : (*neuronOutputCache)[(*edge)->getPrevNeuron()]) - (*centerCoordinate), 2);
	}

	// Sqrt
	euclideanDistance = sqrt(euclideanDistance);
	
	return euclideanDistance;
}

AbstractInputFunction* EuclideanDistance::getInputFunctionCopy()
{
	return new EuclideanDistance(*this);
}
