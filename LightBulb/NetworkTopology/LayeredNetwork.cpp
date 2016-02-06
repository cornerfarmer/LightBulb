// Includes
#include "NetworkTopology/LayeredNetwork.hpp"
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

LayeredNetworkOptions::LayeredNetworkOptions()
{
	enableShortcuts = false;
	neuronsPerLayerCount = std::vector<unsigned int>();
	useBiasNeuron = false;
	activationFunction = NULL;
	inputFunction = NULL;
	outputFunction = NULL;
	threshold = NULL;
}

LayeredNetworkOptions::~LayeredNetworkOptions()
{
	delete(activationFunction);
	delete(inputFunction);
	delete(outputFunction);
	delete(threshold);
}

LayeredNetworkOptions::LayeredNetworkOptions(const LayeredNetworkOptions &obj)
{
	*this = obj;
	activationFunction = obj.activationFunction->getActivationFunctionCopy();
	inputFunction = obj.inputFunction->getInputFunctionCopy();
	outputFunction = obj.outputFunction->getOutputFunctionCopy();
	threshold = obj.threshold->getCopy();
}



LayeredNetwork::~LayeredNetwork()
{

}

LayeredNetwork::LayeredNetwork()
{
	// TODO: Maybe remove this constructor
}

LayeredNetwork::LayeredNetwork(LayeredNetworkOptions &options_)
{
	// Copy all options
	options.reset(new LayeredNetworkOptions(options_));

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


void LayeredNetwork::buildNetwork()
{
	// If the given outputNeuronsIndices vector was empty, fill it with the standard values
	if (options->outputNeuronsIndices.empty())
	{
		for (unsigned int i = 0; i < options->neuronsPerLayerCount.back(); i++)
			options->outputNeuronsIndices.push_back(i);
	}
	layerOffsets.resize(options->neuronsPerLayerCount.size() + 1);
	// Clear all neurons
	netInputs.clear();
	activations.clear();
	weights.clear();
	weights.resize(getLayerCount() - 1);
	activations.resize(getLayerCount());
	netInputs.resize(getLayerCount());
	int totalNeuronCount = 0;
	for (int l = 0; l < getLayerCount(); l++)
	{
		layerOffsets[l] = totalNeuronCount;
		netInputs[l] = Eigen::VectorXd(options->neuronsPerLayerCount[l] + 1);
		activations[l] = Eigen::VectorXd(options->neuronsPerLayerCount[l] + 1);
		if (l > 0)
		{
			weights[l - 1] = Eigen::MatrixXd(options->neuronsPerLayerCount[l], options->neuronsPerLayerCount[l - 1] + 1);
		}
		totalNeuronCount += options->neuronsPerLayerCount[l];
	}
	layerOffsets[getLayerCount()] = totalNeuronCount;

}

std::vector<int> LayeredNetwork::getLayerOffsets()
{
	return layerOffsets;
}


void LayeredNetwork::addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters)
{
	throw std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

AbstractNeuron* LayeredNetwork::addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer)
{
	throw std::logic_error("addNeuronIntoLayer() is not yet implemented");
}

void LayeredNetwork::addNewLayer(int layerIndex, int initialNeuronCount)
{
	throw std::logic_error("addNewLayer() is not yet implemented");
}

int LayeredNetwork::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

int LayeredNetwork::getNeuronCountInLayer(int layerNr)
{
	return options->neuronsPerLayerCount[layerNr];
}

double LayeredNetwork::getBiasWeightOfNeuron(int layerNr, int neuronNr)
{
	if (!options->useBiasNeuron)
		throw std::logic_error("The network does not use a bias neuron");
	return weights[layerNr](neuronNr, weights[layerNr].rows() - 1);
}

std::vector<double> LayeredNetwork::getAfferentWeights(int layerNr, int neuronNr)
{
	std::vector<double> afferentWeights(weights[layerNr].col(neuronNr).data(), weights[layerNr].col(neuronNr).data() + weights[layerNr].rows());
	return afferentWeights;
}

std::vector<std::vector<StandardNeuron*>>* LayeredNetwork::getNeurons()
{
	throw std::logic_error("getNeurons() is not yet implemented");
}

std::vector<Eigen::MatrixXd>* LayeredNetwork::getWeights()
{
	return &weights;
}

std::vector<Eigen::VectorXd>* LayeredNetwork::getActivations()
{
	return &activations;
}

std::vector<Eigen::VectorXd>* LayeredNetwork::getNetInputs()
{
	return &netInputs;
}

void LayeredNetwork::randomizeWeights(double randStart, double randEnd)
{
	for (auto layer = weights.begin(); layer != weights.end(); layer++)
	{
		for (auto i = 0; i < layer->cols(); i++)
		{
			for (auto j = 0; j < layer->rows(); j++)
			{
				do {
					(*layer)(i, j) = randGenerator.next() * (randEnd - randStart) + randStart;
				} while ((*layer)(i, j) == 0);
			}
		}
	}
}

int LayeredNetwork::getEdgeCount()
{
	int edgeCount = 0;
	for (int layerIndex = 0; layerIndex < weights.size(); layerIndex++)
	{
		edgeCount += weights[layerIndex].size();
	}
	return edgeCount;
}

void LayeredNetwork::resetActivation()
{
	for (auto layer = activations.begin(); layer != activations.end(); layer++)
	{
		for (auto i = 0; i != layer->cols() - 1; i++)
		{
			(*layer)(i) = 0;
		}
	}
}

void LayeredNetwork::horizontalMergeWith(LayeredNetwork& otherNetwork)
{
	throw std::logic_error("horizontalMergeWith() is not yet implemented");
}

void LayeredNetwork::mergeWith(LayeredNetwork& otherNetwork)
{
	throw std::logic_error("mergeWith() is not yet implemented");
}

void LayeredNetwork::refreshNeuronsPerLayerCounters()
{
	throw std::logic_error("refreshNeuronsPerLayerCounters() is not yet implemented");
}

std::unique_ptr<std::map<Edge*, bool>> LayeredNetwork::getNonRecurrentEdges()
{
	throw std::logic_error("getNonRecurrentEdges() is not yet implemented");
}

void LayeredNetwork::removeNeuronFromLayer(int layerIndex, int neuronIndex)
{
	throw std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

void LayeredNetwork::removeNeuronFromLayer(int layerIndex, AbstractNeuron* neuronToRemove)
{
	throw std::logic_error("removeNeuronFromLayer() is not yet implemented");
}

std::vector<AbstractNeuron*>* LayeredNetwork::getInputNeurons()
{
	throw std::logic_error("getInputNeurons() is not yet implemented");
}

std::vector<StandardNeuron*>* LayeredNetwork::getOutputNeurons()
{
	throw std::logic_error("getOutputNeurons() is not yet implemented");
}

void LayeredNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs)
{
	throw std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void LayeredNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs)
{
	throw std::logic_error("getAllNeuronNetInputs() is not yet implemented");
}

void LayeredNetwork::getOutput(std::vector<std::pair<bool, double>> &outputVector)
{
	int outputVectorIndex = 0;
	for (auto outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		outputVector[outputVectorIndex++] = std::make_pair(true, activations.back()(*outputNeuronIndex));
	}
}

void LayeredNetwork::setInput(std::vector<std::pair<bool, double>>* inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		activations[0](i) = (*inputVector)[i].second;
	}
}

void LayeredNetwork::getOutput(std::vector<double> &outputVector)
{
	int outputVectorIndex = 0;
	for (auto outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		outputVector[outputVectorIndex++] = activations.back()(*outputNeuronIndex);
	}
}

void LayeredNetwork::setInput(std::vector<double>* inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		activations.front()[i] = (*inputVector)[i];
	}
}


BiasNeuron* LayeredNetwork::getBiasNeuron()
{
	throw std::logic_error("getBiasNeuron() is not yet implemented");
}

int LayeredNetwork::getOutputSize()
{
	return options->outputNeuronsIndices.size();
}

void LayeredNetwork::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	if (!dynamic_cast<LayeredNetwork*>(&otherNetwork))
		throw std::logic_error("You can not mix topology types when calling copyWeightsFrom on a LayeredNetwork");

	weights = static_cast<LayeredNetwork*>(&otherNetwork)->weights;
}


void LayeredNetwork::refreshNetInputsForLayer(int layerNr)
{
	netInputs[layerNr].noalias() = weights[layerNr - 1] * activations[layerNr - 1];
}

void LayeredNetwork::refreshActivationsForLayer(int layerNr)
{
	for (int i = 0; i < activations[layerNr].cols(); i++)
	{
		activations[layerNr](i) = options->activationFunction->execute(netInputs[layerNr](i), options->threshold);
	}
}


double LayeredNetwork::calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork)
{
	double distance = 0;

	auto weights1 = getWeights();
	auto weights2 = static_cast<LayeredNetwork*>(&otherNetwork)->getWeights();

	auto layer1 = weights1->begin();
	auto layer2 = weights2->begin();
	for (; layer1 != weights1->end(); layer1++, layer2++)
	{
		for (int i = 0; i < layer1->cols(); i++)
		{
			for (int j = 0; j < layer1->rows(); j++)
			{
				distance += abs((*layer1)(i,j) - (*layer2)(i, j));
			}
		}
	}

	//distance = sqrt(distance);

	//std::cout << (int)distance << std::endl;
	return distance;

}

