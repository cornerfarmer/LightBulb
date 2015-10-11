// Includes
#include "Learning/ResilientLearningRateHelper.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"


ResilientLearningRateHelper::ResilientLearningRateHelper(ResilientLearningRateHelperOptions* options_) 
{
	options = options_;
}

ResilientLearningRateHelper::ResilientLearningRateHelper() 
{
	options = NULL;
}

void ResilientLearningRateHelper::initialize(NeuralNetwork &neuralNetwork)
{
	// Make sure the previous learning rates map is empty
	previousLearningRates.clear();
}

double ResilientLearningRateHelper::getLearningRate(Edge* edge, double gradient)
{
	// If there is no prevous learning rate, set it to the start value
	if (previousLearningRates.count(edge) == 0)
		previousLearningRates[edge] = options->learningRateStart;

	double learningRate = 0;

	// Only do something if the gradient is not 0
	if (gradient != 0)
	{		
		// Set the new learning rate from the last one
		learningRate = previousLearningRates[edge];		

		// Switch the sign of the gradient (We want to decrease, not to increase the totalError!)
		gradient *= -1;

		// If the sign of the gradient equals the sign of the last learning rate
		if (previousLearningRates[edge] * gradient > 0)
			learningRate *= options->learningRateGrowFac; // Increase the new learning rate
		else if (previousLearningRates[edge] * gradient < 0)
			learningRate *= options->learningRateShrinkFac;	 // Decrease the new learning rate
	
		// Make sure the new learningRate is between learningRateMin and learningRateMax
 		learningRate = std::max(options->learningRateMin, std::min(options->learningRateMax, std::abs(learningRate)));

		// Set the sign of the learningRate to the sign of the gradient
		learningRate *= (gradient > 0 ? 1 : -1);
	}

	// Save the new learningRate
	previousLearningRates[edge] = learningRate;

	return learningRate;
}

void ResilientLearningRateHelper::printDebugOutput()
{
	// Calculate the absolute sum of all learningRates
	double totalLearningRate = 0;
	for (auto previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
		totalLearningRate += abs(previousLearningRate->second); 
	// Print the totalLearningRate
	std::cout << "totalLR :" << std::fixed << std::setprecision(10) << totalLearningRate << " ";
}

bool ResilientLearningRateHelper::learningHasStopped()
{
	// If the previousLearningRates map is not empty (so we have done at least one iteration)
	if (!previousLearningRates.empty())
	{
		bool learningHasStopped = true;
		// If there is any learningRate, which can still change the totalError dont stop the learning process
		double totalLearningRate = 0;
		for (auto previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
		{
			// If the learning rate is in the allowed range, continue learning
			if (abs(previousLearningRate->second) > options->learningRateMin && abs(previousLearningRate->second) < options->learningRateMax)
				learningHasStopped = false;
		
			totalLearningRate += abs(previousLearningRate->second);
		}

		// If the totalLearningRate is below the minium stop the learning process
		if (totalLearningRate < options->minLearningRate)
			learningHasStopped = true;

		return learningHasStopped;
	}
	else
		return false;
}

