// Includes
#include "Function\CylinderFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes
#include <limits>
#include <stdexcept>

CylinderFunction::CylinderFunction(double neighborhoodTimeFac_)
{
	neighborhoodTimeFac = neighborhoodTimeFac_;
}

double CylinderFunction::execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
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
	return (*structure->getNeighborhoodDistances())[neuron][activatedNeuron] < maxDistance; 
}

AbstractNeighborhoodFunction* CylinderFunction::getNeighborhoodFunctionCopy()
{
	return new CylinderFunction(*this);
}