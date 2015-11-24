// Includes
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "Neuron/InputNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/BiasNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NeuronFactory/AbstractNeuronFactory.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Function/AbstractInputFunction.hpp"
#include "Function/AbstractOutputFunction.hpp"
#include "Neuron/AbstractThreshold.hpp"
// Library includes
#include <exception>
#include <math.h>

FastLayeredNetworkOptions::FastLayeredNetworkOptions()
{
	enableShortcuts = false;
	neuronsPerLayerCount = std::vector<unsigned int>();
	useBiasNeuron = false;
	activationFunction = NULL;
	inputFunction = NULL;
	outputFunction = NULL;
	threshold = NULL;
}

FastLayeredNetworkOptions::~FastLayeredNetworkOptions()
{
	delete(activationFunction);
	delete(inputFunction);
	delete(outputFunction);
	delete(threshold);
}

FastLayeredNetworkOptions::FastLayeredNetworkOptions(const FastLayeredNetworkOptions &obj)
{
	*this = obj;
	activationFunction = obj.activationFunction->getActivationFunctionCopy();
	inputFunction = obj.inputFunction->getInputFunctionCopy();
	outputFunction = obj.outputFunction->getOutputFunctionCopy();
	threshold = obj.threshold->getCopy();
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
	if (!options->activationFunction)
		throw std::invalid_argument("The given activationFunction is not valid");
	if (!options->inputFunction)
		throw std::invalid_argument("The given inputFunction is not valid");
	if (!options->outputFunction)
		throw std::invalid_argument("The given outputFunction is not valid");
	if (!options->threshold)
		throw std::invalid_argument("The given threshold is not valid");

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
	layerOffsets.resize(options->neuronsPerLayerCount.size());
	
	// Clear all neurons
	netInputs.clear();
	activations.clear();
	weights.clear();
	int totalNeuronCount = 0;
	for (int l = 0; l < getLayerCount(); l++)
	{
		layerOffsets[l] = totalNeuronCount;
		totalNeuronCount += options->neuronsPerLayerCount[l];
	}
	if (options->useBiasNeuron)
		totalNeuronCount += 1;
	netInputs.resize(totalNeuronCount, 0);
	activations.resize(totalNeuronCount, 0);
	weights.resize(totalNeuronCount, std::vector<double>(totalNeuronCount, 1));
	if (options->useBiasNeuron)
		activations.back() = 1;
}


void FastLayeredNetwork::addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters)
{
	throw std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

AbstractNeuron* FastLayeredNetwork::addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer)
{
	throw std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

void FastLayeredNetwork::addNewLayer(int layerIndex, int initialNeuronCount)
{
	throw std::logic_error("addNewLayer() is not yet implemented");
}

int FastLayeredNetwork::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

std::vector<std::vector<StandardNeuron*>>* FastLayeredNetwork::getNeurons()
{
	throw std::logic_error("getNeurons() is not yet implemented");
}

std::vector<std::vector<double>>* FastLayeredNetwork::getWeights()
{
	return &weights;
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
	for (auto activation = activations.begin() + options->neuronsPerLayerCount.front(); activation != activations.end() - options->useBiasNeuron; activation++)
	{
		*activation = 0;
	}
}

void FastLayeredNetwork::horizontalMergeWith(FastLayeredNetwork& otherNetwork)
{
	throw std::logic_error("horizontalMergeWith() is not yet implemented");
}

void FastLayeredNetwork::mergeWith(FastLayeredNetwork& otherNetwork)
{
	throw std::logic_error("mergeWith() is not yet implemented");
}

void FastLayeredNetwork::refreshNeuronsPerLayerCounters()
{
	throw std::logic_error("refreshNeuronsPerLayerCounters() is not yet implemented");
}

std::unique_ptr<std::map<Edge*, bool>> FastLayeredNetwork::getNonRecurrentEdges()
{
	throw std::logic_error("getNonRecurrentEdges() is not yet implemented");
}

void FastLayeredNetwork::removeNeuronFromLayer(int layerIndex, int neuronIndex)
{
	throw std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

void FastLayeredNetwork::removeNeuronFromLayer(int layerIndex, AbstractNeuron* neuronToRemove)
{
	throw std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

std::vector<AbstractNeuron*>* FastLayeredNetwork::getInputNeurons()
{
	throw std::logic_error("getInputNeurons() is not yet implemented");
}

std::vector<StandardNeuron*>* FastLayeredNetwork::getOutputNeurons()
{
	throw std::logic_error("getOutputNeurons() is not yet implemented");
}

void FastLayeredNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs)
{
	throw std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void FastLayeredNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs)
{
	throw std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void FastLayeredNetwork::getOutput(std::vector<std::pair<bool, double>> &outputVector)
{
	int outputVectorIndex = 0;
	for (auto outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		outputVector[outputVectorIndex++] = std::make_pair(true, activations[layerOffsets.back() + *outputNeuronIndex]);
	}
}

void FastLayeredNetwork::setInput(std::vector<std::pair<bool, double>>* inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		activations[i] = (*inputVector)[i].second;
	}
}

BiasNeuron* FastLayeredNetwork::getBiasNeuron()
{
	throw std::logic_error("getBiasNeuron() is not yet implemented");
}

int FastLayeredNetwork::getOutputSize()
{
	return options->outputNeuronsIndices.size();
}

void FastLayeredNetwork::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	if (!dynamic_cast<FastLayeredNetwork*>(&otherNetwork))
		throw std::logic_error("You can not mix topology types when calling copyWeightsFrom on a FastLayeredNetwork");

	weights = static_cast<FastLayeredNetwork*>(&otherNetwork)->weights;
}


void FastLayeredNetwork::refreshNetInputsForLayer(int layerNr)
{
	for (int i = 0; i < options->neuronsPerLayerCount[layerNr]; i++)
	{
		double netInput = 0;
		for (int l = 0; l < weights.size(); l++)
		{
			netInput += weights[l][layerOffsets[layerNr] + i] * activations[l];
		}
		netInputs[layerOffsets[layerNr] + i] = netInput;
	}
}

void FastLayeredNetwork::refreshActivationsForLayer(int layerNr)
{
	for (int i = 0; i < options->neuronsPerLayerCount[layerNr]; i++)
	{
		activations[layerOffsets[layerNr] + i] = options->activationFunction->execute(netInputs[layerOffsets[layerNr] + i], options->threshold);
	}
}


double FastLayeredNetwork::calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork)
{
	double distance = 0;

	auto weights1 = getWeights();
	auto weights2 = static_cast<FastLayeredNetwork*>(&otherNetwork)->getWeights();
	// Go through all edges
	auto neuron2 = weights2->begin();
	for (auto neuron1 = weights1->begin(); neuron1 != weights1->end(); neuron1++, neuron2++)
	{
		auto weight2 = neuron2->begin();
		for (auto weight1 = neuron1->begin(); weight1 != neuron1->end(); weight1++, weight2++)
		{
			// Calculate the weights average and store it inside the first object
			distance += pow(*weight1 - *weight2, 2);
		}
	}

	distance = sqrt(distance);

	//std::cout << (int)distance << std::endl;
	return distance;
}

