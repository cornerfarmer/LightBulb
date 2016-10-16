#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

// Library includes

namespace LightBulb
{
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
		void fillDefaultLearningRuleOptions(AbstractEvolutionLearningRuleOptions* options) const;
	public:
		AbstractEvolutionTrainingPlan();
		void initializeStart() override;
		AbstractEvolutionWorld* getWorld();
		void setWorld(AbstractEvolutionWorld* network_);
	};
}

#include "IO/AbstractEvolutionTrainingPlanIO.hpp"

#endif
