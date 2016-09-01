// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NeuronFactory/AbstractNeuronDescriptionFactory.hpp"
#include "Neuron/NeuronDescription.hpp"
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "Function/OutputFunction/AbstractOutputFunction.hpp"
// Library includes
#include <exception>
#include <math.h>
#include "Random/AbstractRandomGenerator.hpp"


FeedForwardNetworkTopologyOptions::FeedForwardNetworkTopologyOptions()
{
	enableShortcuts = false;
	neuronsPerLayerCount = std::vector<unsigned int>();
	descriptionFactory = NULL;
	useBiasNeuron = true;
}

FeedForwardNetworkTopologyOptions::~FeedForwardNetworkTopologyOptions()
{
	delete(descriptionFactory);
}

FeedForwardNetworkTopologyOptions::FeedForwardNetworkTopologyOptions(const FeedForwardNetworkTopologyOptions &obj)
{
	*this = obj;
	descriptionFactory = obj.descriptionFactory->getCopy();
}

FeedForwardNetworkTopology::~FeedForwardNetworkTopology()
{

}

FeedForwardNetworkTopology::FeedForwardNetworkTopology()
{
	// TODO: Maybe remove this constructor
}



FeedForwardNetworkTopology::FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions &options_)
{
	// Copy all options
	options.reset(new FeedForwardNetworkTopologyOptions(options_));

	// Check if all given options are correct
	if (getLayerCount() < 2)
		throw std::invalid_argument("A layered network must always contain at least two layers (one input and one output layer)");
	if (!options->descriptionFactory)
		throw std::invalid_argument("The given descriptionFactory is not valid");

	// Build the network
	buildNetwork();
}


void FeedForwardNetworkTopology::buildNetwork()
{
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

void FeedForwardNetworkTopology::rebuildActivationsPerLayer(int layerIndex)
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


double FeedForwardNetworkTopology::getNetInput(int layerIndex, int neuronIndex)
{
	return netInputs[layerIndex](neuronIndex);
}

Eigen::VectorXd FeedForwardNetworkTopology::getNetInputsPerLayer(int layerIndex)
{
	return netInputs[layerIndex];
}

Eigen::VectorXd FeedForwardNetworkTopology::getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex)
{
	return weights[layerIndex].row(neuronIndex);
}

Eigen::VectorXd FeedForwardNetworkTopology::getActivationsPerLayer(int layerIndex)
{
	return *activationsPerLayerOut[layerIndex];
}

Eigen::MatrixXd FeedForwardNetworkTopology::getAfferentWeightsPerLayer(int layerIndex)
{
	return weights[layerIndex - 1];
}

Eigen::MatrixXd FeedForwardNetworkTopology::getEfferentWeightsPerLayer(int layerIndex)
{
	return weights[layerIndex].transpose();
}

bool FeedForwardNetworkTopology::usesBiasNeuron()
{
	return options->useBiasNeuron;
}

void FeedForwardNetworkTopology::removeNeuron(int layerIndex, int neuronIndex)
{
	for (int l = layerIndex + 1; l < layerOffsets.size(); l++)
		layerOffsets[l]--;

	options->neuronsPerLayerCount[layerIndex]--;

	for (int i = neuronIndex; i < netInputs[layerIndex].size() - 1; i++)
		netInputs[layerIndex][i] = netInputs[layerIndex][i + 1];
	netInputs[layerIndex].conservativeResize(netInputs[layerIndex].rows() - 1);

	int prevBiasNeuronCount;
	if (!options->enableShortcuts)
		prevBiasNeuronCount = options->useBiasNeuron * layerIndex;
	else
		prevBiasNeuronCount = layerIndex > 0 ? 1 : 0;

	for (int i = layerOffsets[layerIndex] + prevBiasNeuronCount + neuronIndex; i < activations.size() - 1; i++)
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
		if (options->enableShortcuts)
		{
			for (int l = layerIndex; l < weights.size(); l++)
			{
				for (int c = layerOffsets[layerIndex] + prevBiasNeuronCount + neuronIndex; c < weights[l].cols() - 1; c++)
				{
					weights[l].col(c) = weights[l].col(c + 1);
				}
				weights[l].conservativeResize(weights[l].rows(), weights[l].cols() - 1);
			}
		}
		else
		{
			for (int n = neuronIndex; n < weights[layerIndex].cols() - 1; n++)
				weights[layerIndex].col(n) = weights[layerIndex].col(n + 1);
			weights[layerIndex].conservativeResize(weights[layerIndex].rows(), weights[layerIndex].cols() - 1);
		}
	}
}

void FeedForwardNetworkTopology::addNeuron(int layerIndex)
{
	for (int l = layerIndex + 1; l < layerOffsets.size(); l++)
		layerOffsets[l]++;

	options->neuronsPerLayerCount[layerIndex]++;

	netInputs[layerIndex].conservativeResize(netInputs[layerIndex].rows() + 1);
	netInputs[layerIndex](netInputs[layerIndex].rows() - 1) = 0;

	activations.conservativeResize(activations.rows() + 1);
	int prevBiasNeuronCount;
	if (!options->enableShortcuts)
		prevBiasNeuronCount = options->useBiasNeuron * (layerIndex + 1);
	else
		prevBiasNeuronCount = 1;

	for (int i = activations.size() - 1; i >= layerOffsets[layerIndex + 1] + prevBiasNeuronCount; i--)
		activations[i] = activations[i - 1];
	activations[layerOffsets[layerIndex + 1] + prevBiasNeuronCount - 1] = 0;
	
	for (int l = 0; l < getLayerCount(); l++)
		rebuildActivationsPerLayer(l);

	if (layerIndex < weights.size())
	{
		weights[layerIndex].conservativeResize(weights[layerIndex].rows(), weights[layerIndex].cols() + 1);
		weights[layerIndex].col(weights[layerIndex].cols() - 1).setZero();

		if (options->enableShortcuts)
		{
			for (int l = layerIndex + 1; l < weights.size(); l++)
			{
				weights[l].conservativeResize(weights[l].rows(), weights[l].cols() + 1);
				for (int c = weights[l].cols() - 1; c > weights[layerIndex].cols() - 1; c--)
				{
					weights[l].col(c) = weights[l].col(c - 1);
				}
				weights[l].col(weights[layerIndex].cols() - 1).setZero();
			}
		}
	}
	if (layerIndex > 0)
	{
		weights[layerIndex - 1].conservativeResize(weights[layerIndex - 1].rows() + 1, weights[layerIndex - 1].cols());
		weights[layerIndex - 1].row(weights[layerIndex - 1].rows() - 1).setZero();
	}
}

void FeedForwardNetworkTopology::removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex)
{
	weights[layerIndex](weightIndex, neuronIndex) = 0;
}

bool FeedForwardNetworkTopology::existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex)
{
	return weights[layerIndex](weightIndex, neuronIndex) != 0;
}

int FeedForwardNetworkTopology::getNeuronCount()
{
	int neuronCount = 0;
	for (int i = 0; i < options->neuronsPerLayerCount.size(); i++)
		neuronCount += options->neuronsPerLayerCount[i];
	return neuronCount;
}

int FeedForwardNetworkTopology::getInputSize()
{
	return options->neuronsPerLayerCount.front();
}

AbstractNetworkTopology* FeedForwardNetworkTopology::clone()
{
	FeedForwardNetworkTopology* clone = new FeedForwardNetworkTopology(*options);
	clone->copyWeightsFrom(*this);
	return clone;
}

void FeedForwardNetworkTopology::setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights)
{
	weights[layerIndex - 1] = newWeights;
}

double FeedForwardNetworkTopology::getWeight(int layerIndex, int neuronIndex, int edgeIndex)
{
	return weights[layerIndex](neuronIndex, edgeIndex);
}

void FeedForwardNetworkTopology::setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight)
{
	weights[layerIndex](neuronIndex, edgeIndex) = weight;
}

int FeedForwardNetworkTopology::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

std::vector<unsigned int> FeedForwardNetworkTopology::getNeuronCountsPerLayer()
{
	return options->neuronsPerLayerCount;
}

double FeedForwardNetworkTopology::getBiasWeightOfNeuron(int layerNr, int neuronNr)
{
	if (layerNr == 0)
		throw std::logic_error("The first layer does not have a bias weight.");
	return weights[layerNr - 1](neuronNr, weights[layerNr - 1].cols() - 1);
}

std::vector<double> FeedForwardNetworkTopology::getAfferentWeightsPerNeuron(int layerNr, int neuronNr, bool withoutBiasWeight)
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

std::vector<Eigen::MatrixXd>* FeedForwardNetworkTopology::getAllWeights()
{
	return &weights;
}

std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* FeedForwardNetworkTopology::getAllActivations()
{
	return &activationsPerLayerOut;
}

std::vector<Eigen::VectorXd> FeedForwardNetworkTopology::getActivationsCopy()
{
	std::vector<Eigen::VectorXd> copy(activationsPerLayerOut.size());

	for (int i = 0; i < copy.size(); i++)
	{
		copy[i] = *activationsPerLayerOut[i];
	}

	return copy;
}

std::vector<Eigen::VectorXd>* FeedForwardNetworkTopology::getAllNetInputs()
{
	return &netInputs;
}

void FeedForwardNetworkTopology::randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd)
{
	for (auto layer = weights.begin(); layer != weights.end(); layer++)
	{
		for (auto i = 0; i < layer->rows(); i++)
		{
			for (auto j = 0; j < layer->cols(); j++)
			{
				do {
					(*layer)(i, j) = randomGenerator->randDouble(randStart, randEnd);
				} while ((*layer)(i, j) == 0);
			}
		}
	}
}


void FeedForwardNetworkTopology::randomizeDependingOnLayerSize(AbstractRandomGenerator* randomGenerator)
{
	for (auto layer = weights.begin(); layer != weights.end(); layer++)
	{
		double stdv = 1 / std::sqrt(layer->cols());

		for (auto i = 0; i < layer->rows(); i++)
		{
			for (auto j = 0; j < layer->cols(); j++)
			{
				do {
					(*layer)(i, j) = randomGenerator->randDouble(-stdv, stdv);
				} while ((*layer)(i, j) == 0);
			}
		}
	}
}

int FeedForwardNetworkTopology::getEdgeCount()
{
	int edgeCount = 0;
	for (int layerIndex = 0; layerIndex < weights.size(); layerIndex++)
	{
		edgeCount += weights[layerIndex].size();
	}
	return edgeCount;
}

void FeedForwardNetworkTopology::resetActivation()
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

void FeedForwardNetworkTopology::getOutput(std::vector<double> &outputVector)
{
	outputVector.assign(activationsPerLayerIn.back()->data(), activationsPerLayerIn.back()->data() + outputVector.size());
}

void FeedForwardNetworkTopology::setInput(std::vector<double> &inputVector)
{
	for (int i = 0; i < options->neuronsPerLayerCount.front(); i++)
	{
		(*activationsPerLayerIn.front())(i) = (inputVector.size() > i ? inputVector[i] : 0);
	}
}

int FeedForwardNetworkTopology::getOutputSize()
{
	return options->neuronsPerLayerCount.back();
}

void FeedForwardNetworkTopology::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	if (!dynamic_cast<FeedForwardNetworkTopology*>(&otherNetwork))
		throw std::logic_error("You can not mix topology types when calling copyWeightsFrom on a FeedForwardNetworkTopology");

	weights = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->weights;
	activations = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->activations;
	netInputs = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->netInputs;
	options->neuronsPerLayerCount = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->options->neuronsPerLayerCount;
	layerOffsets = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->layerOffsets;
	for (int l = 0; l < getLayerCount(); l++)
		rebuildActivationsPerLayer(l);
}


void FeedForwardNetworkTopology::refreshNetInputsForLayer(int layerNr)
{
	neuronDescriptionsPerLayer[layerNr]->getInputFunction()->execute(layerNr, activationsPerLayerOut, netInputs, weights);
}

void FeedForwardNetworkTopology::refreshActivationsForLayer(int layerNr)
{
	neuronDescriptionsPerLayer[layerNr]->getActivationFunction()->execute(layerNr, activationsPerLayerIn, netInputs);
}


double FeedForwardNetworkTopology::calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork)
{
	double distance = 0;

	auto weights1 = getAllWeights();
	auto weights2 = static_cast<FeedForwardNetworkTopology*>(&otherNetwork)->getAllWeights();

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


double FeedForwardNetworkTopology::getActivation(int layerIndex, int neuronIndex)
{
	return (*activationsPerLayerOut[layerIndex])(neuronIndex);
}

NeuronDescription* FeedForwardNetworkTopology::getInnerNeuronDescription()
{
	return neuronDescriptionsPerLayer.front().get();
}

NeuronDescription* FeedForwardNetworkTopology::getOutputNeuronDescription()
{
	return neuronDescriptionsPerLayer.back().get();
}
