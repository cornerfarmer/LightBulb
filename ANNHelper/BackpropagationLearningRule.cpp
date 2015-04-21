#include "BackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

BackpropagationLearningRule::BackpropagationLearningRule(BackpropagationLearningRuleOptions options_ ,float learningRate_) 
	: AbstractBackpropagationLearningRule(options_)
{
	learningRate = learningRate_;
}

bool BackpropagationLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Start the algorithm
	float totalError = startAlgorithm(neuralNetwork, teacher, activationOrder, false);

	return (totalError <= options.totalErrorGoal);
}

void BackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	edge->setWeight(edge->getWeight() - learningRate * gradient);
}

void BackpropagationLearningRule::printDebugOutput()
{

}

bool BackpropagationLearningRule::learningHasStopped()
{
	return false;
}