// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	SimpleGradientDescent::SimpleGradientDescent(SimpleGradientDescentOptions& options_)
		:AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions(options_))
	{

	}

	SimpleGradientDescent::SimpleGradientDescent()
		: AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions())
	{
	}

	SimpleGradientDescentOptions* SimpleGradientDescent::getOptions()
	{
		return static_cast<SimpleGradientDescentOptions*>(options.get());
	}

	void SimpleGradientDescent::initializeAlgorithm(const AbstractNetworkTopology* networkTopology)
	{
		// If momentum is used
		if (getOptions()->momentum > 0)
		{
			// Initialize the learningRates map
			previousDeltaWeights = *networkTopology->getAllWeights();
			for (int i = 0; i < previousDeltaWeights.size(); i++)
			{
				previousDeltaWeights[i].setZero();
			}
		}
	}

	Eigen::MatrixXd SimpleGradientDescent::calcDeltaWeight(const AbstractNetworkTopology* networkTopology, int layerIndex, const Eigen::MatrixXd& gradients)
	{
		Eigen::MatrixXd deltaWeight;

		// Calc the delta weight
		deltaWeight = -getOptions()->learningRate * gradients;

		// Substract the weightDecay term
		deltaWeight -= getOptions()->weightDecayFac * networkTopology->getAfferentWeightsPerLayer(layerIndex);

		if (getOptions()->momentum > 0) {
			// Add the momentum term
			deltaWeight += getOptions()->momentum * previousDeltaWeights[layerIndex - 1];

			// Set this to the delta weight
			previousDeltaWeights[layerIndex - 1] = deltaWeight;
		}

		return deltaWeight;
	}

	std::string SimpleGradientDescent::printDebugOutput()
	{
		return "";
	}

	bool SimpleGradientDescent::learningHasStopped()
	{
		return false;
	}

}