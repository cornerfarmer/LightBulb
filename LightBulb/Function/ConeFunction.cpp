// Includes
#include "Function\ConeFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes

double ConeFunction::execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
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
	return std::max(0.0, 1 - (*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance); 
}

AbstractNeighborhoodFunction* ConeFunction::getNeighborhoodFunctionCopy()
{
	return new ConeFunction(*this);
}