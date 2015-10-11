// Includes
#include "Function/CylinderFunction.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "NetworkTopology/AbstractSOMStructure.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes

double CylinderFunction::execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
{
	return (*structure->getNeighborhoodDistances())[neuron][activatedNeuron] < maxDistance; 
}

AbstractNeighborhoodFunction* CylinderFunction::getNeighborhoodFunctionCopy()
{
	return new CylinderFunction(*this);
}