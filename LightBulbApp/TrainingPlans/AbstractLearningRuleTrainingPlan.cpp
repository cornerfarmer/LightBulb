#include "AbstractLearningRuleTrainingPlan.hpp"
#include <Learning/BackpropagationLearningRule.hpp>


void AbstractLearningRuleTrainingPlan::run(bool initial)
{
	if (initial)
	{
		learningRule.reset(createLearningRate());
		bool success = learningRule->start();
	} 
	else
	{
		learningRule->resume();
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

std::string AbstractLearningRuleTrainingPlan::getLearningRateName()
{
	return learningRule->getName();
}


void AbstractLearningRuleTrainingPlan::setLogger(AbstractLogger* newLogger)
{
	AbstractTrainingPlan::setLogger(newLogger);
	if (learningRule.get()) {
		learningRule->setLogger(newLogger);
	}
}

std::vector<std::string> AbstractLearningRuleTrainingPlan::getDataSetLabels()
{
	return BackpropagationLearningRule::getDataSetLabels();
}

LearningState* AbstractLearningRuleTrainingPlan::getLearningState()
{
	return learningRule->getLearningState();
}
