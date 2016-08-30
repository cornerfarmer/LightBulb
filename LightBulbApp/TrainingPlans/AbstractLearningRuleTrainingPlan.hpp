#pragma once

#ifndef _ABSTRACTLEARNINGRULETRAININGPLAN_H_
#define _ABSTRACTLEARNINGRULETRAININGPLAN_H_


// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include "Learning/AbstractLearningResult.hpp"
#include "Learning/AbstractLearningRule.hpp"

// Library includes

// Forward declarations

class AbstractLearningRuleTrainingPlan : public AbstractTrainingPlan
{
	template <class Archive>
	friend void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan);
	template <class Archive>
	friend void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan);
private:
	bool pauseRequested;
	std::unique_ptr<AbstractLearningResult> learningResult;
	std::unique_ptr<AbstractLearningRule> learningRule;
protected:
	virtual AbstractLearningRule* createLearningRate() = 0;
	void run(bool initial);
	void tryToPause();
	virtual void fillDefaultLearningRuleOptions(AbstractLearningRuleOptions* options);
public:
	std::vector<std::string> getDataSetLabels();
	LearningState* getLearningState();
	AbstractLearningResult* getLearningResult();
	AbstractLearningRule* getLearningRule();
};

#include "IO/AbstractLearningRuleTrainingPlanIO.hpp"

#endif
