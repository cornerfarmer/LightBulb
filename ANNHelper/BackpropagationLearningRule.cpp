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
	: AbstractBackpropagationLearningRule(*new BackpropagationLearningRuleOptions(options_))
{

}

void BackpropagationLearningRule::initializeBackpropagationLearningAlgorithm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		// Initialize the learningRates vector with the size of the total edge count
		previousDeltaWeights = std::unique_ptr<std::vector<float>>(new std::vector<float>((dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))->getEdgeCount()));
	}
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{

	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		static int edgeIndex = 0;

		if (edgeIndex == 0)
			edgeIndex = edgeIndex;

		// Calc the delta weight, add the momentum term and the weight decay term
		(*previousDeltaWeights)[edgeIndex] = - getOptions()->learningRate * gradient + getOptions()->momentum * (*previousDeltaWeights)[edgeIndex] - getOptions()->weightDecayFac * edge->getWeight();
		// Add the new delta weight to the current weight
		edge->setWeight(edge->getWeight() + (*previousDeltaWeights)[edgeIndex]);

		// Increase the edge counter
		edgeIndex++;
		edgeIndex %= previousDeltaWeights->size();
		
	}
	else // else just add the new delta weight and the weight decay term
		edge->setWeight(edge->getWeight() - getOptions()->learningRate * gradient - getOptions()->weightDecayFac * edge->getWeight());
	
	
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