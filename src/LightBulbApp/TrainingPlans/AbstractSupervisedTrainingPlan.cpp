// Includes
#include "TrainingPlans/AbstractSupervisedTrainingPlan.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	void AbstractSupervisedTrainingPlan::fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions& options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options.neuralNetwork = network;
	}

	AbstractSupervisedTrainingPlan::AbstractSupervisedTrainingPlan()
	{
		network = nullptr;
	}

	void AbstractSupervisedTrainingPlan::initializeStart()
	{
		if (network == nullptr)
		{
			network = createNeuralNetwork();
			network->setName("trained by " + getName());
		}
		network->setState(NN_STATE_TRAINED);
	}

	AbstractNeuralNetwork& AbstractSupervisedTrainingPlan::getNeuralNetwork()
	{
		return *network;
	}

}