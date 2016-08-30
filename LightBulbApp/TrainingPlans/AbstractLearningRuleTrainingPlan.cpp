#include "AbstractLearningRuleTrainingPlan.hpp"


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

void AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(AbstractLearningRuleOptions* options)
{
	options->logger = logger.get();
}

std::vector<std::string> AbstractLearningRuleTrainingPlan::getDataSetLabels()
{
	return learningRule->getDataSetLabels();
}

LearningState* AbstractLearningRuleTrainingPlan::getLearningState()
{
	return learningRule->getLearningState();
}

AbstractLearningResult* AbstractLearningRuleTrainingPlan::getLearningResult()
{
	return learningResult.get();
}

AbstractLearningRule* AbstractLearningRuleTrainingPlan::getLearningRule()
{
	return learningRule.get();
}
