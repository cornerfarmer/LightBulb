#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

// Library includes


// Forward declarations
class AbstractNeuralNetwork;
struct AbstractEvolutionLearningRuleOptions;

class AbstractEvolutionTrainingPlan : public AbstractLearningRuleTrainingPlan
{
	template <class Archive>
	friend void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan);
	template <class Archive>
	friend void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan);
protected:
	std::unique_ptr<AbstractEvolutionWorld> world;
	virtual AbstractEvolutionWorld* createWorld() = 0;
	void fillDefaultLearningRuleOptions(AbstractEvolutionLearningRuleOptions* options);
public:
	AbstractEvolutionTrainingPlan();
	void initializeStart();
	AbstractEvolutionWorld* getWorld();
	void setWorld(AbstractEvolutionWorld* network_);
};

#include "IO/AbstractEvolutionTrainingPlanIO.hpp"

#endif