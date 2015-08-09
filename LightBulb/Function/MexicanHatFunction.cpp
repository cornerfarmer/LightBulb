// Includes
#include "Function\MexicanHatFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes

double MexicanHatFunction::execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance)
{
	return (1 - pow((*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance, 2)) * exp(-1 * pow((*structure->getNeighborhoodDistances())[neuron][activatedNeuron] / maxDistance, 2)); 
}

AbstractNeighborhoodFunction* MexicanHatFunction::getNeighborhoodFunctionCopy()
{
	return new MexicanHatFunction(*this);
}