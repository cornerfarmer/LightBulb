#include "EuclideanDistance.hpp"
#include "Edge.hpp"
#include "AbstractNeuron.hpp"
#include "RBFThreshold.hpp"
#include <stdexcept>

float EuclideanDistance::execute(std::vector<Edge*> &input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);

	// Make sure the given threshold is a RBFThreshold
	if (!rbfThreshold)
		std::invalid_argument("The threshold has to be a RBFThreshold");

	float euclideanDistance = 0.0;

	// Calculate the square of the distance between the output and the center
	for (int i = 0; i < input.size(); i++)
	{
		euclideanDistance += pow(input[i]->getPrevNeuron()->getActivation() - (*rbfThreshold->getCenterVector())[i], 2);
	}

	// Sqrt
	euclideanDistance = sqrt(euclideanDistance);
	
	return euclideanDistance;
}

AbstractInputFunction* EuclideanDistance::getInputFunctionCopy()
{
	return new EuclideanDistance(*this);
}
