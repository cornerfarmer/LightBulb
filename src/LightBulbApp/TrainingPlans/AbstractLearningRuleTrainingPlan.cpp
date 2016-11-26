#include "AbstractLearningRuleTrainingPlan.hpp"

namespace LightBulb
{
	void AbstractLearningRuleTrainingPlan::run(bool initial)
	{
		if (initial)
		{
			learningRule.reset(createLearningRate());
			learningResult.reset(learningRule->start());
		}
		else
		{
			learningResult.reset(learningRule->resume());
		}

		if (isPausing())
			pausingFinished();
		else
			finished();
	}

	void AbstractLearningRuleTrainingPlan::tryToPause()
	{
		learningRule->sendPauseRequest();
	}

	void AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(AbstractLearningRuleOptions& options) const
	{
		options.logger = logger.get();
	}

	std::vector<std::string> AbstractLearningRuleTrainingPlan::getDataSetLabels() const
	{
		return learningRule->getDataSetLabels();
	}

	LearningState& AbstractLearningRuleTrainingPlan::getLearningState()
	{
		return learningRule->getLearningState();
	}

	bool AbstractLearningRuleTrainingPlan::hasLearningState()
	{
		return learningRule.get() != nullptr;
	}

	const AbstractLearningResult& AbstractLearningRuleTrainingPlan::getLearningResult() const
	{
		return *learningResult.get();
	}

	AbstractLearningRule& AbstractLearningRuleTrainingPlan::getLearningRule()
	{
		return *learningRule.get();
	}

	int AbstractLearningRuleTrainingPlan::getSeed() const
	{
		return learningRule->getSeed();
	}
}