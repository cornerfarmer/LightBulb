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

void BackpropagationLearningRule::initialize()
{
	// If we should use a resilient learnig rate
	if (getOptions()->resilientLearningRate)
	{
		// Create a new ResilientLearningRateHelper
		//resilientLearningRateHelper.reset(new ResilientLearningRateHelper(&getOptions()->resilientLearningRateOptions));
		// Set the momentum to zero (Momentum is not compatible with a resilient learning rate
		getOptions()->momentum = 0;
		// A resilient learning rate can only be used offline
		getOptions()->offlineLearning = true;
	}
}

void BackpropagationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Check if all given parameters are correct
	/*if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");*/

	// Create a vector which will contain all delta values of the neurons in the output layer
	deltaVectorOutputLayer.clear();		

	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		// Initialize the learningRates map
		previousDeltaWeights.clear();
	}
}


Eigen::MatrixXd BackpropagationLearningRule::calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	// Calculate the gradient
	// gradient = - Output(prevNeuron) * deltaValue
	Eigen::MatrixXd gradient = (currentNetworkTopology->getActivationVector(layerIndex - 1) * deltaVectorOutputLayer[layerIndex].transpose()).matrix();
	gradient *= -1;
	return gradient;
}

void BackpropagationLearningRule::initializeLayerCalculation(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getLayerCount() - 1)
	{					
		// Compute the delta value: activationFunction'(netInput) * errorValue
		deltaVectorOutputLayer[layerIndex] = (currentNetworkTopology->getOutputActivationFunction()->executeDerivation(currentNetworkTopology->getNetInputVector(layerIndex)).array() + getOptions()->flatSpotEliminationFac) * errormap->back().array();
	}
	else
	{
		Eigen::VectorXd nextLayerErrorValueFactor = currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex + 1) * deltaVectorOutputLayer[layerIndex + 1];

		// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
		deltaVectorOutputLayer[layerIndex] = (currentNetworkTopology->getInnerActivationFunction()->executeDerivation(currentNetworkTopology->getNetInputVector(layerIndex)).array() + getOptions()->flatSpotEliminationFac) * nextLayerErrorValueFactor.array();
	}	
}

Eigen::MatrixXd BackpropagationLearningRule::calculateDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients)
{
	Eigen::MatrixXd deltaWeights;

	// If momentum and not a resilientLearningRate is used
	if (getOptions()->momentum > 0)
	{
		// Calc the delta weight, add the momentum term and the weight decay term
		previousDeltaWeights[layerIndex] = - getOptions()->learningRate * gradients + getOptions()->momentum * previousDeltaWeights[layerIndex] - getOptions()->weightDecayFac * currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex);
		// Set this to the delta weight
		deltaWeights = previousDeltaWeights[layerIndex];
	}
	else 
	{
		// If a resilientLearningRate is used, get the deltaWeight from the helper object, else calculate it the classical way: - learningRate * gradient
		/*if (getOptions()->resilientLearningRate)
			deltaWeights = resilientLearningRateHelper->getLearningRate(edge, gradient);
		else*/
			deltaWeights = - getOptions()->learningRate * gradients;
		
		// Substract the weightDecay term
		deltaWeights -= getOptions()->weightDecayFac * currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex);
	}
	
	return deltaWeights;
}


AbstractActivationOrder* BackpropagationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void BackpropagationLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	Eigen::MatrixXd newWeights = currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex) + calculateDeltaWeight(layerIndex, gradients);
	currentNetworkTopology->setAfferentWeightsPerLayer(layerIndex, newWeights);
}

void BackpropagationLearningRule::printDebugOutput()
{
	//if (getOptions()->resilientLearningRate)
	//	resilientLearningRateHelper->printDebugOutput();
}

bool BackpropagationLearningRule::learningHasStopped()
{
	// TODO: Implement a learning has stopped algorithm if we use a normal learning rate
	//if (getOptions()->resilientLearningRate)
	//	return resilientLearningRateHelper->learningHasStopped();
	//else
		return false;
}

BackpropagationLearningRuleOptions* BackpropagationLearningRule::getOptions()
{
	return static_cast<BackpropagationLearningRuleOptions*>(options.get());
}

void BackpropagationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}

	// If used, initialize the learning rate helper
	//if (getOptions()->resilientLearningRate)
	//	resilientLearningRateHelper->initialize(neuralNetwork);
}