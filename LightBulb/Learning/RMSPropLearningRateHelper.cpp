// Includes
#include "Learning/RMSPropLearningRateHelper.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


RMSPropLearningRateHelper::RMSPropLearningRateHelper(RMSPropLearningRateHelperOptions* options_)
{
	options = options_;
	initialized = false;
}

RMSPropLearningRateHelper::RMSPropLearningRateHelper()
{
	options = NULL;
	initialized = false;
}

void RMSPropLearningRateHelper::initialize(AbstractNeuralNetwork &neuralNetwork)
{
	// Make sure the previous learning rates map is empty
	prevGradient.resize(neuralNetwork.getNetworkTopology()->getWeights()->size());
	for (int i = 0; i < prevGradient.size(); i++)
	{
		prevGradient[i].resizeLike(neuralNetwork.getNetworkTopology()->getWeights()->at(i));
		prevGradient[i].setZero();
	}
	prevSquaredGradient = prevGradient;
	prevDeltaWeights = prevGradient;
	initialized = true;
}

bool RMSPropLearningRateHelper::isInitialized()
{
	return initialized;
}

Eigen::MatrixXd RMSPropLearningRateHelper::getLearningRate(int layerIndex, Eigen::MatrixXd& gradients)
{
	prevGradient[layerIndex - 1] = options->gradientMomentum * prevGradient[layerIndex - 1] + (1 - options->gradientMomentum) * gradients;
	prevSquaredGradient[layerIndex - 1] = options->squaredGradientMomentum * prevSquaredGradient[layerIndex - 1] + (1 - options->squaredGradientMomentum) * gradients.cwiseAbs2();
	
	prevDeltaWeights[layerIndex - 1] = options->deltaWeightsMomentum * prevDeltaWeights[layerIndex - 1] - options->learningRate * gradients.cwiseQuotient(((prevSquaredGradient[layerIndex - 1].array() - prevGradient[layerIndex - 1].cwiseAbs2().array() + options->minSquaredGradient).cwiseSqrt()).matrix());

	return prevDeltaWeights[layerIndex - 1];
}

std::string RMSPropLearningRateHelper::printDebugOutput()
{
	// Print the totalLearningRate
	return "";
}

bool RMSPropLearningRateHelper::learningHasStopped()
{
	return false;
}

