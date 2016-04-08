// Includes
#include "Learning/BackpropagationLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Learning/ResilientLearningRateHelper.hpp"
#include <list>

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions& options_) 
	: AbstractLearningRule(new BackpropagationLearningRuleOptions(options_))
{

	initialize();
}

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_) 
	: AbstractLearningRule(options_)
{

	initialize();
}

std::string BackpropagationLearningRule::getName()
{
	return "Backpropagation";
}

void BackpropagationLearningRule::initialize()
{
	// If we should use a resilient learnig rate
	if (getOptions()->resilientLearningRate)
	{
		// Create a new ResilientLearningRateHelper
		resilientLearningRateHelper.reset(new ResilientLearningRateHelper(&getOptions()->resilientLearningRateOptions));
		// Set the momentum to zero (Momentum is not compatible with a resilient learning rate
		getOptions()->momentum = 0;
		// A resilient learning rate can only be used offline
		getOptions()->offlineLearning = true;
	}
}

void BackpropagationLearningRule::initializeLearningAlgoritm(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");

	// Create a vector which will contain all delta values of the neurons in the output layer
	deltaVectorOutputLayer.clear();		
	deltaVectorOutputLayer.resize(neuralNetwork.getNetworkTopology()->getLayerCount());

	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		// Initialize the learningRates map
		previousDeltaWeights = *neuralNetwork.getNetworkTopology()->getWeights();
		for (int i = 0; i < previousDeltaWeights.size(); i++)
		{
			previousDeltaWeights[i].setZero();
		}
	}
}


Eigen::MatrixXd BackpropagationLearningRule::calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	// Calculate the gradient
	// gradient = - Output(prevNeuron) * deltaValue
	Eigen::MatrixXd gradient = (deltaVectorOutputLayer[layerIndex] * getCurrentNetworkTopology()->getActivationVector(layerIndex - 1).transpose()).matrix();
	gradient *= -1;
	return gradient;
}

void BackpropagationLearningRule::initializeLayerCalculation(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == getCurrentNetworkTopology()->getLayerCount() - 1)
	{					
		// Compute the delta value: activationFunction'(netInput) * errorValue
		deltaVectorOutputLayer[layerIndex] = (getCurrentNetworkTopology()->getOutputActivationFunction()->executeDerivation(getCurrentNetworkTopology()->getNetInputVector(layerIndex)).array() + getOptions()->flatSpotEliminationFac) * errormap->back().array();
	}
	else
	{
		Eigen::VectorXd nextLayerErrorValueFactor = getCurrentNetworkTopology()->getEfferentWeightsPerLayer(layerIndex) * deltaVectorOutputLayer[layerIndex + 1];
		nextLayerErrorValueFactor.conservativeResize(nextLayerErrorValueFactor.rows() - 1);
		// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
		deltaVectorOutputLayer[layerIndex] = (getCurrentNetworkTopology()->getInnerActivationFunction()->executeDerivation(getCurrentNetworkTopology()->getNetInputVector(layerIndex)).array() + getOptions()->flatSpotEliminationFac) * nextLayerErrorValueFactor.array();
	}	
}

Eigen::MatrixXd BackpropagationLearningRule::calculateDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients)
{
	Eigen::MatrixXd deltaWeights;

	// If momentum and not a resilientLearningRate is used
	if (getOptions()->momentum > 0)
	{
		// Calc the delta weight, add the momentum term and the weight decay term
		previousDeltaWeights[layerIndex - 1] = - getOptions()->learningRate * gradients + getOptions()->momentum * previousDeltaWeights[layerIndex - 1] - getOptions()->weightDecayFac * getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex);
		// Set this to the delta weight
		deltaWeights = previousDeltaWeights[layerIndex - 1];
	}
	else 
	{
		// If a resilientLearningRate is used, get the deltaWeight from the helper object, else calculate it the classical way: - learningRate * gradient
		if (getOptions()->resilientLearningRate)
			deltaWeights = resilientLearningRateHelper->getLearningRate(layerIndex, gradients);
		else
			deltaWeights = - getOptions()->learningRate * gradients;
		
		// Substract the weightDecay term
		deltaWeights -= getOptions()->weightDecayFac * getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex);
	}
	
	return deltaWeights;
}


AbstractActivationOrder* BackpropagationLearningRule::getNewActivationOrder(AbstractNeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void BackpropagationLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	Eigen::MatrixXd newWeights = getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex) + calculateDeltaWeight(layerIndex, gradients);
	getCurrentNetworkTopology()->setAfferentWeightsPerLayer(layerIndex, newWeights);
}

std::string BackpropagationLearningRule::printDebugOutput()
{
	if (getOptions()->resilientLearningRate)
		return resilientLearningRateHelper->printDebugOutput();
	else
		return "";
}

bool BackpropagationLearningRule::learningHasStopped()
{
	// TODO: Implement a learning has stopped algorithm if we use a normal learning rate
	if (getOptions()->resilientLearningRate)
		return resilientLearningRateHelper->learningHasStopped();
	else
		return false;
}

BackpropagationLearningRuleOptions* BackpropagationLearningRule::getOptions()
{
	return static_cast<BackpropagationLearningRuleOptions*>(options.get());
}

void BackpropagationLearningRule::initializeTry(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}

	// If used, initialize the learning rate helper
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);
}