// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	RMSPropLearningRate::RMSPropLearningRate(RMSPropLearningRateOptions& options_)
		: AbstractGradientDescentAlgorithm(new RMSPropLearningRateOptions(options_))
	{
	}

	RMSPropLearningRate::RMSPropLearningRate()
		: AbstractGradientDescentAlgorithm(new RMSPropLearningRateOptions())
	{
	}


	RMSPropLearningRateOptions* RMSPropLearningRate::getOptions()
	{
		return static_cast<RMSPropLearningRateOptions*>(options.get());
	}

	void RMSPropLearningRate::initializeAlgorithm(const AbstractNetworkTopology* networkTopology)
	{
		// Make sure the previous learning rates map is empty
		prevGradient.resize(networkTopology->getAllWeights()->size());
		for (int i = 0; i < prevGradient.size(); i++)
		{
			prevGradient[i].resizeLike(networkTopology->getAllWeights()->at(i));
			prevGradient[i].setZero();
		}
		prevSquaredGradient = prevGradient;
		prevDeltaWeights = prevGradient;
	}


	Eigen::MatrixXd RMSPropLearningRate::calcDeltaWeight(const AbstractNetworkTopology* networkTopology, int layerIndex, const Eigen::MatrixXd& gradients)
	{
		prevGradient[layerIndex - 1] = getOptions()->gradientMomentum * prevGradient[layerIndex - 1] + (1 - getOptions()->gradientMomentum) * gradients;
		prevSquaredGradient[layerIndex - 1] = getOptions()->squaredGradientMomentum * prevSquaredGradient[layerIndex - 1] + (1 - getOptions()->squaredGradientMomentum) * gradients.cwiseAbs2();

		prevDeltaWeights[layerIndex - 1] = getOptions()->deltaWeightsMomentum * prevDeltaWeights[layerIndex - 1] - getOptions()->learningRate * gradients.cwiseQuotient(((prevSquaredGradient[layerIndex - 1].array() - prevGradient[layerIndex - 1].cwiseAbs2().array() + getOptions()->minSquaredGradient).cwiseSqrt()).matrix());

		return prevDeltaWeights[layerIndex - 1];
	}


	bool RMSPropLearningRate::learningHasStopped()
	{
		return false;
	}
}

