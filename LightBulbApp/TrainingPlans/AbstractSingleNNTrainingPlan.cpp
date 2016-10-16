// Includes
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	void AbstractSingleNNTrainingPlan::fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions* options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options->neuralNetwork = network;
	}

	AbstractSingleNNTrainingPlan::AbstractSingleNNTrainingPlan()
	{
		network = nullptr;
	}

	void AbstractSingleNNTrainingPlan::initializeStart()
	{
		if (network == nullptr)
		{
			network = createNeuralNetwork();
			network->setName("trained by " + getName());
		}
		network->setState(NN_STATE_TRAINED);
	}

	AbstractNeuralNetwork* AbstractSingleNNTrainingPlan::getNeuralNetwork()
	{
		return network;
	}

	void AbstractSingleNNTrainingPlan::setNeuralNetwork(AbstractNeuralNetwork* network_)
	{
		network = network_;
	}
}