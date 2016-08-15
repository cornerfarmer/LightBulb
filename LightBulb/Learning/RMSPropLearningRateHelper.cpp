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
	prevDeltaWeights.resize(neuralNetwork.getNetworkTopology()->getWeights()->size());
	for (int i = 0; i < prevDeltaWeights.size(); i++)
	{
		prevDeltaWeights[i].resizeLike(neuralNetwork.getNetworkTopology()->getWeights()->at(i));
		prevDeltaWeights[i].setZero();
	}
	initialized = true;
}

bool RMSPropLearningRateHelper::isInitialized()
{
	return initialized;
}

Eigen::MatrixXd RMSPropLearningRateHelper::getLearningRate(int layerIndex, Eigen::MatrixXd& gradients)
{
	prevDeltaWeights[layerIndex - 1] = options->decayFac * prevDeltaWeights[layerIndex - 1] + (1 - options->decayFac) * gradients.cwiseAbs2();
	
	return - options->learningRate * gradients.cwiseQuotient(((prevDeltaWeights[layerIndex - 1].array() + options->minSquaredGradient).cwiseSqrt()).matrix());
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

