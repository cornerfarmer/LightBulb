// Includes
#include "Function/MinimumNetInputActivationFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes
#include <limits>
#include <stdexcept>

namespace LightBulb
{
	double MinimumNetInputActivationFunction::execute(double input)
	{
		throw std::exception("Currently not working");
		//NeuronCompareThreshold* neuronCompareThreshold = dynamic_cast<NeuronCompareThreshold*>(threshold);
		//// Check if the given threshold is a StandardThreshold
		//if (!neuronCompareThreshold)
		//	throw std::invalid_argument("The given threshold has to be a NeuronCompareThreshold");

		//// Go through all other neurons
		//for (auto otherNeuron = neuronCompareThreshold->getNeurons()->begin(); otherNeuron != neuronCompareThreshold->getNeurons()->end(); otherNeuron++)
		//{
		//	// If the other neuron has a lower netInput, set the activation to zero
		//	if ((*otherNeuron)->getNetInput() < input || ((*otherNeuron)->getNetInput() == input && (*otherNeuron)->getThreshold() < threshold))
		//		return 0;
		//}

		//// This neuron has the lowest netInput => set Activation to 1
		//return 1;
	}

	double MinimumNetInputActivationFunction::executeDerivation(double input)
	{
		// A MinimumNetInputActivationFunction does not have a derivation => throw a exception
		throw std::logic_error("There is no derivation of the MinimumNetInputActivationFunction");
	}

	AbstractActivationFunction* MinimumNetInputActivationFunction::getActivationFunctionCopy()
	{
		return new MinimumNetInputActivationFunction(*this);
	}

	double MinimumNetInputActivationFunction::getMaximum()
	{
		return 1;
	}

	double MinimumNetInputActivationFunction::getMinimum()
	{
		return 0;
	}

	bool MinimumNetInputActivationFunction::hasAMaxAndMinimum()
	{
		return true;
	}
}