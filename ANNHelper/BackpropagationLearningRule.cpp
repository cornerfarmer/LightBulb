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

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions options_ ,float learningRate_, float momentum_, bool offlineLearning_) 
	: AbstractBackpropagationLearningRule(options_)
{
	learningRate = learningRate_;
	momentum = momentum_;
	offlineLearning = offlineLearning_;
}

bool BackpropagationLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// If momentum is used
	if (momentum > 0)
	{
		// Initialize the learningRates vector with the size of the total edge count
		previousDeltaWeights = std::unique_ptr<std::vector<float>>(new std::vector<float>((dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))->getEdgeCount()));
	}

	// Start the algorithm
	float totalError = startAlgorithm(neuralNetwork, teacher, activationOrder, offlineLearning);

	return (totalError <= options.totalErrorGoal);
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{

	// If momentum is used
	if (momentum > 0)
	{
		static int edgeIndex = 0;

		if (edgeIndex == 0)
			edgeIndex = edgeIndex;

		// Calc the delta weight, add the momentum term and the weight decay term
		(*previousDeltaWeights)[edgeIndex] = - learningRate * gradient + momentum * (*previousDeltaWeights)[edgeIndex] - options.weightDecayFac * edge->getWeight();
		// Add the new delta weight to the current weight
		edge->setWeight(edge->getWeight() + (*previousDeltaWeights)[edgeIndex]);

		// Increase the edge counter
		edgeIndex++;
		edgeIndex %= previousDeltaWeights->size();
		
	}
	else // else just add the new delta weight and the weight decay term
		edge->setWeight(edge->getWeight() - learningRate * gradient - options.weightDecayFac * edge->getWeight());
	
	
}

void BackpropagationLearningRule::printDebugOutput()
{

}

bool BackpropagationLearningRule::learningHasStopped()
{
	return false;
}