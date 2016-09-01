// Includes
#include "Learning/Supervised/GradientDecentAlgorithms/SimpleGradientDecent.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


SimpleGradientDecent::SimpleGradientDecent(SimpleGradientDecentOptions& options_)
	:AbstractGradientDecentAlgorithm(new SimpleGradientDecentOptions(options_))
{

}

SimpleGradientDecent::SimpleGradientDecent()
	: AbstractGradientDecentAlgorithm(new SimpleGradientDecentOptions())
{
}

SimpleGradientDecentOptions* SimpleGradientDecent::getOptions()
{
	return static_cast<SimpleGradientDecentOptions*>(options.get());
}

void SimpleGradientDecent::initializeAlgorithm(AbstractNeuralNetwork &neuralNetwork)
{
	this->neuralNetwork = &neuralNetwork;
	// If momentum is used
	if (getOptions()->momentum > 0)
	{
		// Initialize the learningRates map
		previousDeltaWeights = *neuralNetwork.getNetworkTopology()->getAllWeights();
		for (int i = 0; i < previousDeltaWeights.size(); i++)
		{
			previousDeltaWeights[i].setZero();
		}
	}
}

Eigen::MatrixXd SimpleGradientDecent::calcDeltaWeight(int layerIndex, Eigen::MatrixXd& gradients)
{
	Eigen::MatrixXd deltaWeight;

	// Calc the delta weight
	deltaWeight = -getOptions()->learningRate * gradients;
	
	// Substract the weightDecay term
	deltaWeight -= getOptions()->weightDecayFac * neuralNetwork->getNetworkTopology()->getAfferentWeightsPerLayer(layerIndex);

	if (getOptions()->momentum > 0) {
		// Add the momentum term
		deltaWeight += getOptions()->momentum * previousDeltaWeights[layerIndex - 1];

		// Set this to the delta weight
		previousDeltaWeights[layerIndex - 1] = deltaWeight;
	}

	return deltaWeight;
}

std::string SimpleGradientDecent::printDebugOutput()
{
	return "";
}

bool SimpleGradientDecent::learningHasStopped()
{
	return false;
}

