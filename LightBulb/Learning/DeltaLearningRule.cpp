// Includes
#include "Learning/DeltaLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/RBFNetwork.hpp"


DeltaLearningRule::DeltaLearningRule(DeltaLearningRuleOptions &options_)
	: AbstractLearningRule(new DeltaLearningRuleOptions(options_)) 
{
	// Check if all given options are correct
	// Check if the given neuronPlacer is valid
	if (getOptions()->changeWeightsBeforeLearning && getOptions()->neuronPlacer == NULL)
		throw std::invalid_argument("The given neuronPlacer is not valid");
	// If we should use a resilient learnig rate
	if (getOptions()->resilientLearningRate)
	{
		// Create a new ResilientLearningRateHelper
		resilientLearningRateHelper.reset(new ResilientLearningRateHelper(&getOptions()->resilientLearningRateOptions));
		// A resilient learning rate can only be used offline
		getOptions()->offlineLearning = true;
	}
}

void DeltaLearningRule::initializeLearningAlgoritm(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (!dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()) && dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::invalid_argument("The given neuralNetwork has to contain exactly two layers");
	if (dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()) && (getOptions()->changeWeightsBeforeLearning && !getOptions()->neuronPlacer))
		throw new std::invalid_argument("The neuronPlacer in the given options cannot be null");
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);
}

AbstractActivationOrder* DeltaLearningRule::getNewActivationOrder(AbstractNeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

Eigen::MatrixXd DeltaLearningRule::calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getLayerCount() - 1)
	{
		// Use the delta rule: deltaWeight = Output(prevNeuron) * errorValue
		Eigen::MatrixXd gradient = (errormap->back() * currentNetworkTopology->getActivationVector(layerIndex - 1).transpose()).matrix();
		gradient *= -1;
		return gradient;
	}
	else
		return Eigen::MatrixXd::Zero(currentNeuralNetwork->getNetworkTopology()->getNeuronCountInLayer(layerIndex), currentNeuralNetwork->getNetworkTopology()->getNeuronCountInLayer(layerIndex - 1));
}

void DeltaLearningRule::initializeTry(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher)
{
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);

		// If the given network is a rbfNetwork replace all RBFNeurons with the help of the choosen neuronPlacer
		if (dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()))
			getOptions()->neuronPlacer->doPlacing(*dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()), teacher);
	}
}

DeltaLearningRuleOptions* DeltaLearningRule::getOptions()
{
	return static_cast<DeltaLearningRuleOptions*>(options.get());
}

void DeltaLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	if (getOptions()->resilientLearningRate)
	{
		// Add the learningRate and the weight decay term to the weight
		Eigen::MatrixXd newWeights = currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex) + resilientLearningRateHelper->getLearningRate(layerIndex, gradients);
		currentNetworkTopology->setAfferentWeightsPerLayer(layerIndex, newWeights);
	}
	else
	{
		// Just add the weight (learningRate * gradient)
		Eigen::MatrixXd newWeights = currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex) - getOptions()->learningRate * gradients;
		currentNetworkTopology->setAfferentWeightsPerLayer(layerIndex, newWeights);
	}
}

bool DeltaLearningRule::learningHasStopped()
{
	if (getOptions()->resilientLearningRate)
		return resilientLearningRateHelper->learningHasStopped();
	else
		return false;
}

void DeltaLearningRule::printDebugOutput()
{
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->printDebugOutput();
}