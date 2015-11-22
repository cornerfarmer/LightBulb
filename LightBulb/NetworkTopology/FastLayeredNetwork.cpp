// Includes
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "Neuron/InputNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/BiasNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NeuronFactory/AbstractNeuronFactory.hpp"
// Library includes
#include <exception>

FastLayeredNetworkOptions::FastLayeredNetworkOptions()
{
	enableShortcuts = false;
	neuronsPerLayerCount = std::vector<unsigned int>();
	useBiasNeuron = false;
}

FastLayeredNetworkOptions::~FastLayeredNetworkOptions()
{
}

FastLayeredNetworkOptions::FastLayeredNetworkOptions(const FastLayeredNetworkOptions &obj)
{
	*this = obj;
}



FastLayeredNetwork::~FastLayeredNetwork()
{

}

FastLayeredNetwork::FastLayeredNetwork()
{
	// TODO: Maybe remove this constructor
}

FastLayeredNetwork::FastLayeredNetwork(FastLayeredNetworkOptions &options_)
{
	// Copy all options
	options.reset(new FastLayeredNetworkOptions(options_));

	// Check if all given options are correct
	if (getLayerCount() < 2)
		throw std::invalid_argument("A layered network must always contain at least two layers (one input and one output layer)");

	// Build the network
	buildNetwork();		
}


void FastLayeredNetwork::buildNetwork()
{
	// If the given outputNeuronsIndices vector was empty, fill it with the standard values
	if (options->outputNeuronsIndices.empty())
	{
		for (unsigned int i = 0; i < options->neuronsPerLayerCount.back(); i++)
			options->outputNeuronsIndices.push_back(i);
	}
	
	// Clear all neurons
	netInputs.clear();
	activations.clear();
	weights.clear();
	int totalNeuronCount = 0;
	for (int l = 0; l < getLayerCount(); l++)
	{
		totalNeuronCount += options->neuronsPerLayerCount[l];
	}
	if (options->useBiasNeuron)
		totalNeuronCount += 1;
	netInputs.resize(totalNeuronCount, 0);
	activations.resize(totalNeuronCount, 0);
	weights.resize(totalNeuronCount, std::vector<double>(totalNeuronCount, 1));
}


void FastLayeredNetwork::addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters)
{
	std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

AbstractNeuron* FastLayeredNetwork::addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer)
{
	std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

void FastLayeredNetwork::addNewLayer(int layerIndex, int initialNeuronCount)
{
	std::logic_error("addNewLayer() is not yet implemented");
}

int FastLayeredNetwork::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

std::vector<std::vector<StandardNeuron*>>* FastLayeredNetwork::getNeurons()
{
	std::logic_error("getNeurons() is not yet implemented");
}

void FastLayeredNetwork::randomizeWeights(double randStart, double randEnd)
{
	for (auto column = weights.begin(); column != weights.end(); column++)
	{
		for (auto weight = column->begin(); weight != column->end(); weight++)
		{
			do {
				*weight = (double)rand() / RAND_MAX * (randEnd - randStart) + randStart;
			} while (*weight == 0);
		}
	}
}

int FastLayeredNetwork::getEdgeCount()
{
	return weights[0].size() * weights.size();
}

void FastLayeredNetwork::resetActivation()
{
	for (auto column = weights.begin(); column != weights.end(); column++)
	{
		for (auto weight = column->begin(); weight != column->end(); weight++)
		{
			*weight = 0;
		}
	}
}

void FastLayeredNetwork::horizontalMergeWith(FastLayeredNetwork& otherNetwork)
{
	std::logic_error("horizontalMergeWith() is not yet implemented");
}

void FastLayeredNetwork::mergeWith(FastLayeredNetwork& otherNetwork)
{
	std::logic_error("mergeWith() is not yet implemented");
}

void FastLayeredNetwork::refreshNeuronsPerLayerCounters()
{
	std::logic_error("refreshNeuronsPerLayerCounters() is not yet implemented");
}

std::unique_ptr<std::map<Edge*, bool>> FastLayeredNetwork::getNonRecurrentEdges()
{
	std::logic_error("getNonRecurrentEdges() is not yet implemented");
}

void FastLayeredNetwork::removeNeuronFromLayer(int layerIndex, int neuronIndex)
{
	std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

void FastLayeredNetwork::removeNeuronFromLayer(int layerIndex, AbstractNeuron* neuronToRemove)
{
	std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

std::vector<AbstractNeuron*>* FastLayeredNetwork::getInputNeurons()
{
	std::logic_error("getInputNeurons() is not yet implemented");
}

std::vector<StandardNeuron*>* FastLayeredNetwork::getOutputNeurons()
{
	std::logic_error("getOutputNeurons() is not yet implemented");
}

void FastLayeredNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs)
{
	std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void FastLayeredNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs)
{
	std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void FastLayeredNetwork::getOutput(std::vector<std::pair<bool, double>> &outputVector)
{

}

void FastLayeredNetwork::setInput(std::vector<std::pair<bool, double>>* inputVector)
{

}

BiasNeuron* FastLayeredNetwork::getBiasNeuron()
{
	std::logic_error("getBiasNeuron() is not yet implemented");
}

