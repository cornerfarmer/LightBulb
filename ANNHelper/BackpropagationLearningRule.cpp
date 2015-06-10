#include "BackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "ResilientLearningRateHelper.hpp"

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
		resilientLearningRateHelper.reset(new ResilientLearningRateHelper(&getOptions()->resilientLearningRateOptions));
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
		// Initialize the learningRates vector with the size of the total edge count
		previousDeltaWeights = std::unique_ptr<std::vector<float>>(new std::vector<float>((dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))->getEdgeCount()));
	}
}


float BackpropagationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == layerCount - 1)
	{		
		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		float gradient = -1 * edge->getPrevNeuron()->getActivation() * deltaVectorOutputLayer[edge->getNextNeuron()];	

		return gradient;
	}
	else
	{		
		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		float gradient = -1 * edge->getPrevNeuron()->getActivation() * deltaVectorOutputLayer[edge->getNextNeuron()];
	
		return gradient;
	}	

	return 0;
}

void BackpropagationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == layerCount - 1)
	{					
		// Compute the delta value: activationFunction'(netInput) * errorValue
		deltaVectorOutputLayer[neuron] = (neuron->executeDerivationOnActivationFunction(neuron->getNetInput()) + getOptions()->flatSpotEliminationFac) * (*errormap)[0][neuron];
	}
	else
	{
		std::list<Edge*>* efferentEdges = neuron->getEfferentEdges();

		// Calc the nextLayerErrorValueFactor
		float nextLayerErrorValueFactor = 0;

		// Go through all efferentEdges of the actual neuron and add to the nextLayerErrorValueFactor: deltaValue * edgeWeight
		int efferentEdgeIndex = 0;
		for (std::list<Edge*>::iterator efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++, efferentEdgeIndex++)
		{
			nextLayerErrorValueFactor += deltaVectorOutputLayer[(*efferentEdge)->getNextNeuron()] * (*efferentEdge)->getWeight();
		}

		// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
		deltaVectorOutputLayer[neuron] = (neuron->executeDerivationOnActivationFunction(neuron->getNetInput()) + getOptions()->flatSpotEliminationFac) * nextLayerErrorValueFactor;					
	}	
}

float BackpropagationLearningRule::calculateDeltaWeight(Edge* edge, float gradient)
{
	float deltaWeight;

	// If momentum and not a resilientLearningRate is used
	if (getOptions()->momentum > 0)
	{
		static int edgeIndex = 0;

		// Calc the delta weight, add the momentum term and the weight decay term
		(*previousDeltaWeights)[edgeIndex] = - getOptions()->learningRate * gradient + getOptions()->momentum * (*previousDeltaWeights)[edgeIndex] - getOptions()->weightDecayFac * edge->getWeight();
		// Set this to the delta weight
		deltaWeight = (*previousDeltaWeights)[edgeIndex];

		// Increase the edge counter
		edgeIndex++;
		edgeIndex %= previousDeltaWeights->size();
		
	}
	else 
	{
		// If a resilientLearningRate is used, get the deltaWeight from the helper object, else calculate it the classical way: - learningRate * gradient
		if (getOptions()->resilientLearningRate)
			deltaWeight = resilientLearningRateHelper->getNextLearningRate(gradient);
		else
			deltaWeight = - getOptions()->learningRate * gradient;
		
		// Substract the weightDecay term
		deltaWeight -= getOptions()->weightDecayFac * edge->getWeight();
	}
	
	return deltaWeight;
}


AbstractActivationOrder* BackpropagationLearningRule::getNewActivationOrder()
{
	return new TopologicalOrder();
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	edge->setWeight(edge->getWeight() + calculateDeltaWeight(edge, gradient));
}

void BackpropagationLearningRule::printDebugOutput()
{
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->printDebugOutput();
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

void BackpropagationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}

	// If used, initialize the learning rate helper
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);
}