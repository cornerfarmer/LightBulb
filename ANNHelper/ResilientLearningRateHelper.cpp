#include "ResilientLearningRateHelper.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"


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
	// Initialize the learningRates vector with the size of the total edge count
	previousLearningRates.clear();
}

float ResilientLearningRateHelper::getLearningRate(Edge* edge, float gradient)
{
	if (previousLearningRates.count(edge) == 0)
		previousLearningRates[edge] = options->learningRateStart;

	float learningRate = 0;

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
	float totalLearningRate = 0;
	for (std::map<Edge*, float>::iterator previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
		totalLearningRate += abs(previousLearningRate->second); 
	// Print the totalLearningRate
	std::cout << "totalLR :" << std::fixed << std::setprecision(10) << totalLearningRate << " ";
}

bool ResilientLearningRateHelper::learningHasStopped()
{
	// If there is any learningRate, which can still change the totalError dont stop the learning process
	for (std::map<Edge*, float>::iterator previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
	{
		if (abs(previousLearningRate->second) > options->learningRateMin && abs(previousLearningRate->second) < options->learningRateMax)
			return false;
	}
	return true;

}

