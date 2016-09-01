// Includes
#include "Learning/Supervised/GradientDecentAlgorithms/RMSPropLearningRate.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


RMSPropLearningRate::RMSPropLearningRate(RMSPropLearningRateOptions& options_)
	: AbstractGradientDecentAlgorithm(new RMSPropLearningRateOptions(options_)) 
{
}

RMSPropLearningRate::RMSPropLearningRate()
	:AbstractGradientDecentAlgorithm(new RMSPropLearningRateOptions())
{
}


RMSPropLearningRateOptions* RMSPropLearningRate::getOptions()
{
	return static_cast<RMSPropLearningRateOptions*>(options.get());
}

void RMSPropLearningRate::initializeAlgorithm(AbstractNeuralNetwork &neuralNetwork)
{
	// Make sure the previous learning rates map is empty
	prevGradient.resize(neuralNetwork.getNetworkTopology()->getAllWeights()->size());
	for (int i = 0; i < prevGradient.size(); i++)
	{
		prevGradient[i].resizeLike(neuralNetwork.getNetworkTopology()->getAllWeights()->at(i));
		prevGradient[i].setZero();
	}
	prevSquaredGradient = prevGradient;
	prevDeltaWeights = prevGradient;
}


Eigen::MatrixXd RMSPropLearningRate::calcDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients)
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

