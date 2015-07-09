#include "Learning\BackpropagationLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "Learning\ResilientLearningRateHelper.hpp"

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
		// Initialize the learningRates map
		previousDeltaWeights.clear();
	}
}


double BackpropagationLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getNeurons()->size() - 1)
	{		
		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		double gradient = -1 * edge.getPrevNeuron()->getActivation() * deltaVectorOutputLayer[edge.getNextNeuron()];	

		return gradient;
	}
	else
	{		
		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		double gradient = -1 * edge.getPrevNeuron()->getActivation() * deltaVectorOutputLayer[edge.getNextNeuron()];
	
		return gradient;
	}	

	return 0;
}

void BackpropagationLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	// If its the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getNeurons()->size() - 1)
	{					
		// Compute the delta value: activationFunction'(netInput) * errorValue
		deltaVectorOutputLayer[&neuron] = (neuron.executeDerivationOnActivationFunction(neuron.getNetInput()) + getOptions()->flatSpotEliminationFac) * (*errormap).rbegin()->second[&neuron];
	}
	else
	{
		std::list<Edge*>* efferentEdges = neuron.getEfferentEdges();

		// Calc the nextLayerErrorValueFactor
		double nextLayerErrorValueFactor = 0;

		// Go through all efferentEdges of the actual neuron and add to the nextLayerErrorValueFactor: deltaValue * edgeWeight
		int efferentEdgeIndex = 0;
		for (std::list<Edge*>::iterator efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++, efferentEdgeIndex++)
		{
			nextLayerErrorValueFactor += deltaVectorOutputLayer[(*efferentEdge)->getNextNeuron()] * (*efferentEdge)->getWeight();
		}

		// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
		deltaVectorOutputLayer[&neuron] = (neuron.executeDerivationOnActivationFunction(neuron.getNetInput()) + getOptions()->flatSpotEliminationFac) * nextLayerErrorValueFactor;					
	}	
}

double BackpropagationLearningRule::calculateDeltaWeight(Edge* edge, double gradient)
{
	double deltaWeight;

	// If momentum and not a resilientLearningRate is used
	if (getOptions()->momentum > 0)
	{
		// Calc the delta weight, add the momentum term and the weight decay term
		previousDeltaWeights[edge] = - getOptions()->learningRate * gradient + getOptions()->momentum * previousDeltaWeights[edge] - getOptions()->weightDecayFac * edge->getWeight();
		// Set this to the delta weight
		deltaWeight = previousDeltaWeights[edge];		
	}
	else 
	{
		// If a resilientLearningRate is used, get the deltaWeight from the helper object, else calculate it the classical way: - learningRate * gradient
		if (getOptions()->resilientLearningRate)
			deltaWeight = resilientLearningRateHelper->getLearningRate(edge, gradient);
		else
			deltaWeight = - getOptions()->learningRate * gradient;
		
		// Substract the weightDecay term
		deltaWeight -= getOptions()->weightDecayFac * edge->getWeight();
	}
	
	return deltaWeight;
}


AbstractActivationOrder* BackpropagationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, double gradient)
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