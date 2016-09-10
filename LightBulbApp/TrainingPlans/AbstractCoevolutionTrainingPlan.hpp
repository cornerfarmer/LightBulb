#pragma once

#ifndef _ABSTRACTCOEVOLUTIONEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTCOEVOLUTIONEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractEvolutionLearningRuleOptions;
	struct BipartiteEvolutionLearningRuleOptions;
	struct EvolutionLearningRuleOptions;

	class AbstractCoevolutionTrainingPlan : public AbstractEvolutionTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan);
	protected:
		std::unique_ptr<AbstractEvolutionWorld> parasiteWorld;
		virtual AbstractEvolutionWorld* createParasiteWorld() = 0;
		void fillDefaultLearningRuleOptions(BipartiteEvolutionLearningRuleOptions* options);
		void fillDefaultEvolutionLearningRule1Options(EvolutionLearningRuleOptions* options);
		void fillDefaultEvolutionLearningRule2Options(EvolutionLearningRuleOptions* options);
	public:
		void initializeStart() override;
		AbstractEvolutionWorld* getParasiteWorld();
		void setParasiteWorld(AbstractEvolutionWorld* world_);
	};
}

#include "IO/AbstractCoevolutionTrainingPlanIO.hpp"

#endif
