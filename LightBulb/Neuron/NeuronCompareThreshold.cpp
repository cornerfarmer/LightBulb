// Includes
#include "Neuron/NeuronCompareThreshold.hpp"

NeuronCompareThreshold::NeuronCompareThreshold(std::vector<StandardNeuron*>* neurons_)
{
	neurons = neurons_;
}

std::vector<StandardNeuron*>* NeuronCompareThreshold::getNeurons()
{
	return neurons;
}

void NeuronCompareThreshold::setNeurons(std::vector<StandardNeuron*>* neurons_)
{
	neurons = neurons_;
}

AbstractThreshold* NeuronCompareThreshold::getCopy()
{
	return new NeuronCompareThreshold(*this);
}