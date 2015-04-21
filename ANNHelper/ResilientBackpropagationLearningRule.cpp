#include "ResilientBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

ResilientBackpropagationLearningRule::ResilientBackpropagationLearningRule(BackpropagationLearningRuleOptions options_) 
	: AbstractBackpropagationLearningRule(options_)
{
	learningRateGrowFac = 1.2;
	learningRateShrinkFac = 0.5;
	learningRateMax = 50;
	learningRateMin = 0.000001f;
	learningRateStart = 0.2f;
}

bool ResilientBackpropagationLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Initialize the learningRates vector with the size of the total edge count
	previousLearningRates = std::unique_ptr<std::vector<float>>(new std::vector<float>((dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))->getEdgeCount()));

	// Reset all learning rates to learningRateStart
	for (std::vector<float>::iterator learningRate = previousLearningRates->begin(); learningRate != previousLearningRates->end(); learningRate++)
		*learningRate = learningRateStart;

	// Start the algorithm
	float totalError = startAlgorithm(neuralNetwork, teacher, activationOrder, true);

	return (totalError <= options.totalErrorGoal);
}

void ResilientBackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	static int learningRateIndex = 0;

	if (gradient!=0)
	{		
		float learningRate = (*previousLearningRates)[learningRateIndex];

		if (learningRateIndex == 0)
			learningRateIndex = learningRateIndex;

		if (-(*previousLearningRates)[learningRateIndex] * gradient > 0)
			learningRate *= learningRateGrowFac;
		else if (-(*previousLearningRates)[learningRateIndex] * gradient < 0)
			learningRate *= learningRateShrinkFac;	
	
 		learningRate = std::max(learningRateMin, std::min(learningRateMax, std::abs(learningRate)));

		learningRate *= (gradient > 0 ? -1 : 1);

		edge->setWeight(edge->getWeight() + learningRate);		

		//// If the momentum is greater than 0
		//if (options.momentum > 0)
		//{
		//	// Add the momentum term to the calculated weight: momentum * prevDeltaWeight
		//	edge->setWeight(edge->getWeight() + options.momentum * (*previousLearningRates)[learningRateIndex]);
		//}

		(*previousLearningRates)[learningRateIndex] = learningRate;
	}
	else
		(*previousLearningRates)[learningRateIndex] = 0;

	learningRateIndex++;
	learningRateIndex %= previousLearningRates->size();
}

void ResilientBackpropagationLearningRule::printDebugOutput()
{
	float totalLearningRate = 0;
	for (std::vector<float>::iterator previousLearningRate = (*previousLearningRates).begin(); previousLearningRate != (*previousLearningRates).end(); previousLearningRate++)
		totalLearningRate += abs(*previousLearningRate); 
	std::cout << std::fixed << std::setprecision(10) << totalLearningRate << " ";
}

bool ResilientBackpropagationLearningRule::learningHasStopped()
{
	for (std::vector<float>::iterator previousLearningRate = (*previousLearningRates).begin(); previousLearningRate != (*previousLearningRates).end(); previousLearningRate++)
	{
		if (abs(*previousLearningRate) > 1.2000000e-006f)
			return false;
	}
	return true;

}