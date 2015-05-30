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

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions options_) 
	: AbstractBackpropagationLearningRule(new BackpropagationLearningRuleOptions(options_))
{

	initialize();
}

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_) 
	: AbstractBackpropagationLearningRule(options_)
{

	initialize();
}

void BackpropagationLearningRule::initialize()
{
	if (getOptions()->resilientLearningRate)
	{
		resilientLearningRateHelper.reset(new ResilientLearningRateHelper(&getOptions()->resilientLearningRateOptions));
		getOptions()->momentum = 0;
		getOptions()->offlineLearning = true;
	}
}

void BackpropagationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	AbstractBackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher);
	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		// Initialize the learningRates vector with the size of the total edge count
		previousDeltaWeights = std::unique_ptr<std::vector<float>>(new std::vector<float>((dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))->getEdgeCount()));
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
	AbstractBackpropagationLearningRule::initializeTry(neuralNetwork, teacher);
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);
}