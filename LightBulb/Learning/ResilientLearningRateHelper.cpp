// Includes
#include "Learning/ResilientLearningRateHelper.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


ResilientLearningRateHelper::ResilientLearningRateHelper(ResilientLearningRateHelperOptions* options_) 
{
	options = options_;
	initialized = false;
}

ResilientLearningRateHelper::ResilientLearningRateHelper() 
{
	options = NULL;
	initialized = false;
}

void ResilientLearningRateHelper::initialize(AbstractNeuralNetwork &neuralNetwork)
{
	// Make sure the previous learning rates map is empty
	previousLearningRates = *neuralNetwork.getNetworkTopology()->getWeights();
	for (int i = 0; i < previousLearningRates.size(); i++)
	{
		previousLearningRates[i].setConstant(options->learningRateStart);
	}
	initialized = true;
}

bool ResilientLearningRateHelper::isInitialized()
{
	return initialized;
}

Eigen::MatrixXd ResilientLearningRateHelper::getLearningRate(int layerIndex, Eigen::MatrixXd& gradients)
{
	// Switch the sign of the gradient (We want to decrease, not to increase the totalError!)
	gradients *= -1;

	for (int i = 0; i < gradients.rows(); i++)
	{
		for (int j = 0; j < gradients.cols(); j++)
		{
			if (gradients(i, j) != 0)
			{
				// If the sign of the gradient equals the sign of the last learning rate
				if (previousLearningRates[layerIndex - 1](i, j) * gradients(i, j) > 0)
					previousLearningRates[layerIndex - 1](i, j) *= options->learningRateGrowFac; // Increase the new learning rate
				else if (previousLearningRates[layerIndex - 1](i, j) * gradients(i, j) < 0)
					previousLearningRates[layerIndex - 1](i, j) *= options->learningRateShrinkFac;	 // Decrease the new learning rate

				// Make sure the new learningRate is between learningRateMin and learningRateMax
				previousLearningRates[layerIndex - 1](i, j) = std::max(options->learningRateMin, std::min(options->learningRateMax, std::abs(previousLearningRates[layerIndex - 1](i, j))));

				// Set the sign of the learningRate to the sign of the gradient
				previousLearningRates[layerIndex - 1](i, j) *= (gradients(i, j) > 0 ? 1 : -1);
			}
			else
				previousLearningRates[layerIndex - 1](i, j) = 0;
		}
	}

	return previousLearningRates[layerIndex - 1];
}

std::string ResilientLearningRateHelper::printDebugOutput()
{
	// Calculate the absolute sum of all learningRates
	double totalLearningRate = 0;
	for (auto previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
		totalLearningRate += previousLearningRate->cwiseAbs().sum(); 
	// Print the totalLearningRate
	return "totalLR :" + std::to_string(totalLearningRate) + " ";
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
			if (abs(previousLearningRate->maxCoeff()) > options->learningRateMin && abs(previousLearningRate->minCoeff()) < options->learningRateMax)
				learningHasStopped = false;
		
			totalLearningRate += previousLearningRate->cwiseAbs().sum();
		}

		// If the totalLearningRate is below the minium stop the learning process
		if (totalLearningRate < options->minLearningRate)
			learningHasStopped = true;

		return learningHasStopped;
	}
	else
		return false;
}

