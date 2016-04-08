#pragma once

#ifndef _ABSTRACTLEARNINGRULETRAININGPLAN_H_
#define _ABSTRACTLEARNINGRULETRAININGPLAN_H_


// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <Learning/BackpropagationLearningRule.hpp>
#include "Teaching/Teacher.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class AbstractLearningRuleTrainingPlan : public AbstractTrainingPlan
{
	template <class Archive>
	friend void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan);
	template <class Archive>
	friend void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan);
private:
	bool pauseRequested;
	std::unique_ptr<AbstractLearningRule> learningRule;
protected:
	virtual AbstractLearningRule* createLearningRate() = 0;
	void run(bool initial);
	void tryToPause();
	void fillDefaultLearningRuleOptions(AbstractLearningRuleOptions* options);
public:
	void setLogger(AbstractLogger* newLogger);
	std::vector<std::string> getDataSetLabels();
	LearningState* getLearningState();
};
#endif
