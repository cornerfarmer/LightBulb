#define _USE_MATH_DEFINES
// Includes
#include "Function\CosinusFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes


double CosinusFunction::execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
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
	return cos(std::min((*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance * M_PI / 2, M_PI / 2)); 
}

AbstractNeighborhoodFunction* CosinusFunction::getNeighborhoodFunctionCopy()
{
	return new CosinusFunction(*this);
}