// Includes
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NeuronFactory/AbstractNeuronDescriptionFactory.hpp"
#include "Neuron/NeuronDescription.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Function/AbstractInputFunction.hpp"
#include "Function/AbstractOutputFunction.hpp"
// Library includes
#include <exception>
#include <math.h>

LayeredNetworkOptions::LayeredNetworkOptions()
{
	enableShortcuts = false;
	neuronsPerLayerCount = std::vector<unsigned int>();
	descriptionFactory = NULL;
	useBiasNeuron = true;
}

LayeredNetworkOptions::~LayeredNetworkOptions()
{
	delete(descriptionFactory);
}

LayeredNetworkOptions::LayeredNetworkOptions(const LayeredNetworkOptions &obj)
{
	*this = obj;
	descriptionFactory = obj.descriptionFactory->getCopy();
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
	if (!options->descriptionFactory)
		throw std::invalid_argument("The given descriptionFactory is not valid");

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
	int totalNeuronCount = 0;
	for (int l = 0; l < getLayerCount(); l++)
	{
		layerOffsets[l] = totalNeuronCount;
		totalNeuronCount += options->neuronsPerLayerCount[l];
	}
	layerOffsets[getLayerCount()] = totalNeuronCount;

	// Clear all neurons
	netInputs.clear();
	weights.clear();
	weights.resize(getLayerCount() - 1);
	activations.resize(getLayerCount());
	netInputs.resize(getLayerCount());
	activationsPerLayerIn.resize(getLayerCount());
	activationsPerLayerOut.resize(getLayerCount());
	neuronDescriptionsPerLayer.resize(getLayerCount());
	if (options->enableShortcuts)
	{
		activations = Eigen::VectorXd(totalNeuronCount + options->useBiasNeuron);
		if (options->useBiasNeuron) {
			activations(0) = 1;
		}
	}
	else
	{
		activations = Eigen::VectorXd(totalNeuronCount + options->useBiasNeuron * getLayerCount());
		if (options->useBiasNeuron) {
			for (int l = 0; l < getLayerCount(); l++)
				activations(l + layerOffsets[l]) = 1;
		}
	}
	for (int l = 0; l < getLayerCount(); l++)
	{
		netInputs[l] = Eigen::VectorXd(options->neuronsPerLayerCount[l]);
		rebuildActivationsPerLayer(l);
		if (l > 0)
		{
			weights[l - 1] = Eigen::MatrixXd::Zero(activationsPerLayerIn[l]->size(), activationsPerLayerOut[l - 1]->size());
		}
		if (l == getLayerCount() - 1)
			neuronDescriptionsPerLayer[l].reset(options->descriptionFactory->createOutputNeuronDescription());
		else 
			neuronDescriptionsPerLayer[l].reset(options->descriptionFactory->createInnerNeuronDescription());
	}
	
	
}

void LayeredNetwork::rebuildActivationsPerLayer(int layerIndex)
{
	if (options->enableShortcuts)
	{
		activationsPerLayerIn[layerIndex].reset(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), options->useBiasNeuron + layerOffsets[layerIndex], options->neuronsPerLayerCount[layerIndex]));
		activationsPerLayerOut[layerIndex].reset(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), 0, layerOffsets[layerIndex + 1] + options->useBiasNeuron));
	}
	else
	{
		activationsPerLayerIn[layerIndex].reset(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), options->useBiasNeuron * (layerIndex + 1) + layerOffsets[layerIndex], options->neuronsPerLayerCount[layerIndex]));
		activationsPerLayerOut[layerIndex].reset(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), options->useBiasNeuron * layerIndex + layerOffsets[layerIndex], options->neuronsPerLayerCount[layerIndex] + options->useBiasNeuron));
	}
}

std::vector<int> LayeredNetwork::getLayerOffsets()
{
	return layerOffsets;
}

double LayeredNetwork::getNetInput(int layerIndex, int neuronIndex)
{
	return netInputs[layerIndex](neuronIndex);
}

Eigen::VectorXd LayeredNetwork::getNetInputVector(int layerIndex)
{
	return netInputs[layerIndex];
}

Eigen::VectorXd LayeredNetwork::getEfferentWeightVector(int layerIndex, int neuronIndex)
{
	return weights[layerIndex].row(neuronIndex);
}

AbstractActivationFunction* LayeredNetwork::getInnerActivationFunction()
{
	return options->descriptionFactory->getOutputActivationFunction();
}

Eigen::VectorXd LayeredNetwork::getActivationVector(int layerIndex)
{
	return *activationsPerLayerOut[layerIndex];
}

Eigen::MatrixXd LayeredNetwork::getAfferentWeightsPerLayer(int layerIndex)
{
	return weights[layerIndex - 1];
}

Eigen::MatrixXd LayeredNetwork::getEfferentWeightsPerLayer(int layerIndex)
{
	return weights[layerIndex].transpose();
}

bool LayeredNetwork::usesBiasNeuron()
{
	return options->useBiasNeuron;
}

void LayeredNetwork::removeNeuron(int layerIndex, int neuronIndex)
{
	for (int l = layerIndex + 1; l < layerOffsets.size(); l++)
		layerOffsets[l]--;

	options->neuronsPerLayerCount[layerIndex]--;

	for (int i = neuronIndex; i < netInputs[layerIndex].size() - 1; i++)
		netInputs[layerIndex][i] = netInputs[layerIndex][i + 1];
	netInputs[layerIndex].conservativeResize(netInputs[layerIndex].rows() - 1);

	for (int i = layerOffsets[layerIndex] + options->useBiasNeuron * layerIndex + neuronIndex; i < activations.size() - 1; i++)
		activations[i] = activations[i + 1];
	activations.conservativeResize(activations.rows() - 1);

	for (int l = 0; l < getLayerCount(); l++)
		rebuildActivationsPerLayer(l);

	if (layerIndex > 0)
	{
		for (int n = neuronIndex; n < weights[layerIndex - 1].rows() - 1; n++)
			weights[layerIndex - 1].row(n) = weights[layerIndex - 1].row(n + 1);
		weights[layerIndex - 1].conservativeResize(weights[layerIndex - 1].rows() - 1, weights[layerIndex - 1].cols());
	}
	if (layerIndex < weights.size())
	{
		for (int n = neuronIndex; n < weights[layerIndex].cols() - 1; n++)
			weights[layerIndex].col(n) = weights[layerIndex].col(n + 1);
		weights[layerIndex].conservativeResize(weights[layerIndex].rows(), weights[layerIndex].cols() - 1);
	}
}

void LayeredNetwork::addNeuron(int layerIndex)
{
	for (int l = layerIndex + 1; l < layerOffsets.size(); l++)
		layerOffsets[l]++;

	options->neuronsPerLayerCount[layerIndex]++;

	netInputs[layerIndex].conservativeResize(netInputs[layerIndex].rows() + 1);
	netInputs[layerIndex](netInputs[layerIndex].rows() - 1) = 0;

	activations.conservativeResize(activations.rows() + 1);
	for (int i = activations.size() - 1; i >= layerOffsets[layerIndex + 1] + options->useBiasNeuron * (layerIndex + 1); i--)
		activations[i] = activations[i - 1];
	activations[layerOffsets[layerIndex + 1] + options->useBiasNeuron * (layerIndex + 1) - 1] = 0;
	
	for (int l = 0; l < getLayerCount(); l++)
		rebuildActivationsPerLayer(l);

	if (layerIndex < weights.size())
	{
		weights[layerIndex].conservativeResize(weights[layerIndex].rows(), weights[layerIndex].cols() + 1);
		weights[layerIndex].col(weights[layerIndex].cols() - 1).setZero();
	}
	if (layerIndex > 0)
	{
		weights[layerIndex - 1].conservativeResize(weights[layerIndex - 1].rows() + 1, weights[layerIndex - 1].cols());
		weights[layerIndex - 1].row(weights[layerIndex - 1].rows() - 1).setZero();
	}
}

void LayeredNetwork::setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights)
{
	weights[layerIndex - 1] = newWeights;
}

int LayeredNetwork::getAfferentEdgeCount(int layerIndex, int neuronIndex)
{
	if (layerIndex == 0)
		return 0;
	else
		return options->neuronsPerLayerCount[layerIndex - 1];
}

double LayeredNetwork::getPrevNeuronActivation(int layerIndex, int neuronIndex, int edgeIndex)
{
	return (*activationsPerLayerOut[layerIndex - 1])[edgeIndex];
}

double LayeredNetwork::getWeight(int layerIndex, int neuronIndex, int edgeIndex)
{
	return weights[layerIndex](neuronIndex, edgeIndex);
}

void LayeredNetwork::setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight)
{
	weights[layerIndex](neuronIndex, edgeIndex) = weight;
}

AbstractActivationFunction* LayeredNetwork::getOutputActivationFunction()
{
	return options->descriptionFactory->getOutputActivationFunction();
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

std::vector<unsigned int> LayeredNetwork::getNeuronCountsPerLayer()
{
	return options->neuronsPerLayerCount;
}

double LayeredNetwork::getBiasWeightOfNeuron(int layerNr, int neuronNr)
{
	if (layerNr == 0)
		throw std::logic_error("The first layer does not have a bias weight.");
	return weights[layerNr - 1](neuronNr, weights[layerNr - 1].cols() - 1);
}

std::vector<double> LayeredNetwork::getAfferentWeights(int layerNr, int neuronNr, bool withoutBiasWeight)
{
	if (layerNr == 0)
		throw std::logic_error("The first layer does not have afferent weights.");
	std::vector<double> afferentWeights(weights[layerNr - 1].cols() - withoutBiasWeight);
	for (int i = 0; i < afferentWeights.size(); i++)
	{
		afferentWeights[i] = weights[layerNr - 1](neuronNr, i);
	}
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

std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* LayeredNetwork::getActivations()
{
	return &activationsPerLayerOut;
}

std::vector<Eigen::VectorXd>* LayeredNetwork::getNetInputs()
{
	return &netInputs;
}

void LayeredNetwork::randomizeWeights(double randStart, double randEnd)
{
	for (auto layer = weights.begin(); layer != weights.end(); layer++)
	{
		for (auto i = 0; i < layer->rows(); i++)
		{
			for (auto j = 0; j < layer->cols(); j++)
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
	if (options->enableShortcuts)
	{
		for (int i = options->useBiasNeuron; i < activations.rows(); i++)
		{
			activations(i) = 0;
		}
	}
	else
	{
		for (int i = 0; i < activations.rows(); i++)
		{
			activations(i) = 0;
		}
		if (options->useBiasNeuron)
		{
			for (int l = 0; l < getLayerCount(); l++)
				activations(l + layerOffsets[l]) = 1;
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
		outputVector[outputVectorIndex++] = std::make_pair(true, (*activationsPerLayerIn.back())(*outputNeuronIndex));
	}
}

void LayeredNetwork::setInput(std::vector<std::pair<bool, double>> &inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		(*activationsPerLayerIn[0])(i) = inputVector[i].second;
	}
}

void LayeredNetwork::getOutput(std::vector<double> &outputVector)
{
	outputVector.assign(activationsPerLayerIn.back()->data(), activationsPerLayerIn.back()->data() + outputVector.size());
}

void LayeredNetwork::setInput(std::vector<double> &inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		(*activationsPerLayerIn.front())(i) = inputVector[i];
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
	neuronDescriptionsPerLayer[layerNr]->getInputFunction()->execute(layerNr, activationsPerLayerOut, netInputs, weights);
}

void LayeredNetwork::refreshActivationsForLayer(int layerNr)
{
	neuronDescriptionsPerLayer[layerNr]->getActivationFunction()->execute(layerNr, activationsPerLayerIn, netInputs);
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

