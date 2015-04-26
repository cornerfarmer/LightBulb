#include "ResilientBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

ResilientBackpropagationLearningRule::ResilientBackpropagationLearningRule(BackpropagationLearningRuleOptions options_) 
	: AbstractBackpropagationLearningRule(options_)
{
	learningRateGrowFac = 1.2f;
	learningRateShrinkFac = 0.5f;
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

	// Return if learning was successful
	return (totalError <= options.totalErrorGoal);
}

void ResilientBackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	// Initialize the learningRateIndex
	static int learningRateIndex = 0;

	// Only do something if the gradient is not 0
	if (gradient != 0)
	{		
		// Set the new learning rate from the last one
		float learningRate = (*previousLearningRates)[learningRateIndex];

		// Switch the sign of the gradient (We want to decrease, not to increase the totalError!)
		gradient *= -1;

		// If the sign of the gradient equals the sign of the last learning rate
		if ((*previousLearningRates)[learningRateIndex] * gradient > 0)
			learningRate *= learningRateGrowFac; // Increase the new learning rate
		else if ((*previousLearningRates)[learningRateIndex] * gradient < 0)
			learningRate *= learningRateShrinkFac;	 // Decrease the new learning rate
	
		// Make sure the new learningRate is between learningRateMin and learningRateMax
 		learningRate = std::max(learningRateMin, std::min(learningRateMax, std::abs(learningRate)));

		// Set the sign of the learningRate to the sign of the gradient
		learningRate *= (gradient > 0 ? 1 : -1);

		// Add the learningRate and the weight decay term to the weight
		edge->setWeight(edge->getWeight() + learningRate  - options.weightDecayFac * edge->getWeight());		

		// Save the new learningRate
		(*previousLearningRates)[learningRateIndex] = learningRate;
	}
	else
		(*previousLearningRates)[learningRateIndex] = 0;

	// Increase the learningRateIndex
	learningRateIndex++;
	learningRateIndex %= previousLearningRates->size();
}

void ResilientBackpropagationLearningRule::printDebugOutput()
{
	// Calculate the absolute sum of all learningRates
	float totalLearningRate = 0;
	for (std::vector<float>::iterator previousLearningRate = (*previousLearningRates).begin(); previousLearningRate != (*previousLearningRates).end(); previousLearningRate++)
		totalLearningRate += abs(*previousLearningRate); 
	// Print the totalLearningRate
	std::cout << std::fixed << std::setprecision(10) << totalLearningRate << " ";
}

bool ResilientBackpropagationLearningRule::learningHasStopped()
{
	// If there is any learningRate, which can still change the totalError dont stop the learning process
	for (std::vector<float>::iterator previousLearningRate = (*previousLearningRates).begin(); previousLearningRate != (*previousLearningRates).end(); previousLearningRate++)
	{
		if (abs(*previousLearningRate) > 1.2000000e-006f)
			return false;
	}
	return true;

}