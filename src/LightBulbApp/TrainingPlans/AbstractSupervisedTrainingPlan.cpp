// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/AbstractSupervisedTrainingPlan.hpp"
#include "LightBulb/Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	void AbstractSupervisedTrainingPlan::fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions& options) const
	{
		AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
		options.neuralNetwork = network;
	}

	void AbstractSupervisedTrainingPlan::pausingFinished()
	{
		AbstractTrainingPlan::pausingFinished();
		network->setState(NN_STATE_READY);
	}
	
	void AbstractSupervisedTrainingPlan::finished()
	{
		AbstractTrainingPlan::finished();
		network->setState(NN_STATE_READY);
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
