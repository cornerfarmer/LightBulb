#define _USE_MATH_DEFINES
// Includes
#include "Function/CosinusFunction.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "NetworkTopology/AbstractSOMStructure.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes


double CosinusFunction::execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
{
	return cos(std::min((*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance * M_PI / 2, M_PI / 2)); 
}

AbstractNeighborhoodFunction* CosinusFunction::getNeighborhoodFunctionCopy()
{
	return new CosinusFunction(*this);
}