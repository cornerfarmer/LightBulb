// Includes
#include "Function\GaussianRBFFunction.hpp"
#include "Neuron\RBFThreshold.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes
#include <limits>
#include <stdexcept>

double GaussianRBFFunction::execute(double input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold is a RBFThreshold
	if (!rbfThreshold)
		throw std::invalid_argument("The given threshold has to be a RBFThreshold");

	// Return the value of the gaussian rbf: e^(-input^2/(2*width^2)
	return exp(-pow(input, 2) / (2 * pow(rbfThreshold->getWidth(), 2)));
}

double GaussianRBFFunction::executeDerivation(double input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold was a RBFThreshold
	if (!rbfThreshold)
		throw std::invalid_argument("The given threshold has to be a RBFThreshold");

	// TODO: Implement the derivation even if it is not used
	return 0;

}

AbstractActivationFunction* GaussianRBFFunction::getActivationFunctionCopy()
{
	return new GaussianRBFFunction(*this);
}

double GaussianRBFFunction::getMaximum()
{
	throw std::logic_error("A GaussianRBFFunction does not have a maximum");
}

double GaussianRBFFunction::getMinimum()
{
	throw std::logic_error("A GaussianRBFFunction does not have a minimum");
}

bool GaussianRBFFunction::hasAMaxAndMinimum()
{
	return true;
}

double GaussianRBFFunction::execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, int timeStep)
{
	StandardNeuron* activatedNeuron = NULL;
	for (auto neuron = threshold->getNeurons()->begin(); neuron != threshold->getNeurons()->end(); neuron++)
	{
		if ((*neuron)->getActivation() == (*neuron)->getActivationFunction()->getMaximum())
		{
			activatedNeuron = *neuron;
			break;
		}
	}
	return exp(-pow((*structure->getNeighborhoodDistances())[neuron][activatedNeuron], 2) / (2 * pow(2.0 / ((timeStep - 1) / 100 + 1), 2))); 
}