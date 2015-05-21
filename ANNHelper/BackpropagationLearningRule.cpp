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

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions options_) 
	: AbstractBackpropagationLearningRule(new BackpropagationLearningRuleOptions(options_))
{

}

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions* options_) 
	: AbstractBackpropagationLearningRule(options_)
{

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

	// If momentum is used
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
	else // else just set it to the new delta weight and the weight decay term
		deltaWeight = - getOptions()->learningRate * gradient - getOptions()->weightDecayFac * edge->getWeight();
	
	return deltaWeight;
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	edge->setWeight(edge->getWeight() + calculateDeltaWeight(edge, gradient));
}

void BackpropagationLearningRule::printDebugOutput()
{

}

bool BackpropagationLearningRule::learningHasStopped()
{
	return false;
}

BackpropagationLearningRuleOptions* BackpropagationLearningRule::getOptions()
{
	return static_cast<BackpropagationLearningRuleOptions*>(options.get());
}