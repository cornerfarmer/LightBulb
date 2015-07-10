// Includes
#include "Function\EuclideanDistance.hpp"
#include "Neuron\Edge.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\RBFThreshold.hpp"
// Library includes
#include <stdexcept>

double EuclideanDistance::execute(std::list<Edge*> &input, AbstractThreshold* threshold, double additionalInput, std::map<AbstractNeuron*, double>* neuronOutputCache)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);

	// Make sure the given threshold is a RBFThreshold
	if (!rbfThreshold)
		std::invalid_argument("The threshold has to be a RBFThreshold");

	double euclideanDistance = 0.0;

	// Calculate the square of the distance between the output and the center
	std::vector<double>::iterator centerCoordinate = (*rbfThreshold->getCenterVector()).begin();
	for (auto edge = input.begin(); edge != input.end(); edge++, centerCoordinate++)
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
