// Includes
#include "Function/ConeFunction.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "NetworkTopology/AbstractSOMStructure.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes

double ConeFunction::execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
{
	return std::max(0.0, 1 - (*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance); 
}

AbstractNeighborhoodFunction* ConeFunction::getNeighborhoodFunctionCopy()
{
	return new ConeFunction(*this);
}