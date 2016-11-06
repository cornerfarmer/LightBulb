#pragma once

#ifndef _EVOLUTIONLEARNINGRULE_H_
#define _EVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionLearningRule.hpp"

// Library Includes
#include <vector>
#include <memory>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	class AbstractCreationCommand;
	class AbstractSelectionCommand;
	class AbstractMutationCommand;
	class AbstractRecombinationCommand;
	class AbstractExitCondition;
	class AbstractReuseCommand;
	class AbstractFitnessFunction;

#define DATA_SET_FITNESS "Fitness"
#define DATA_AVG_NEURON_COUNT "Average neuron count"
#define DATA_BEST_NEURON_COUNT "Best neuron count"

	enum EvolutionLearningEvents
	{
		EVT_EL_EVOLUTIONSTEP
	};

	struct EvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
	{
		// Holds a few conditions which evaluate if the learning process should be stopped
		std::vector<AbstractExitCondition*> exitConditions;
		// Holds commands for creating new objects
		std::vector<AbstractCreationCommand*> creationCommands;
		// Holds commands for selecting objects which should stay
		std::vector<AbstractSelectionCommand*> selectionCommands;
		// Holds function which can modify the calculated fitness values
		std::vector<AbstractFitnessFunction*> fitnessFunctions;
		// Holds commands for mutating those objects
		std::vector<AbstractMutationCommand*> mutationsCommands;
		// Holds commands for combining two objects into a new one
		std::vector<AbstractRecombinationCommand*> recombinationCommands;
		// Holds commands for directly reusing objects
		std::vector<AbstractReuseCommand*> reuseCommands;
		EvolutionLearningRuleOptions()
		{
			maxTries = 1;
		}
		~EvolutionLearningRuleOptions();
		EvolutionLearningRuleOptions(const EvolutionLearningRuleOptions& other);
		EvolutionLearningRuleOptions(EvolutionLearningRuleOptions&& other) noexcept;
		EvolutionLearningRuleOptions& operator=(EvolutionLearningRuleOptions other);
		friend void swap(EvolutionLearningRuleOptions& lhs, EvolutionLearningRuleOptions& rhs) noexcept;
	};

	// A learingRule for improving NNs with the help of algorithms oriented by the evolution
	class EvolutionLearningRule : public AbstractEvolutionLearningRule, public Observable<EvolutionLearningEvents, EvolutionLearningRule>
	{
		template <class Archive>
		friend void serialize(Archive& archive, EvolutionLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<EvolutionLearningRule>;
	protected:
		std::vector<AbstractEvolutionObject*> notUsedObjects;
		bool doIteration() override;
		bool hasLearningSucceeded() override;
		const EvolutionLearningRuleOptions& getOptions() const;
		void doCalculationAfterLearningProcess() override;
		void setHelperToUsedObjects() override;
		bool exitConditionReached;
		AbstractLearningResult* getLearningResult() override;
	public:
		EvolutionLearningRule(EvolutionLearningRuleOptions& options_);
		EvolutionLearningRule(EvolutionLearningRuleOptions* options_);
		EvolutionLearningRule();
		// Executes the learning process
		void initializeTry() override;
		static std::string getName();
		std::vector<std::string> getDataSetLabels() const override;
		void setLogger(AbstractLogger& logger) override;
	};
}

#include "IO/EvolutionLearningRuleIO.hpp"

#endif
