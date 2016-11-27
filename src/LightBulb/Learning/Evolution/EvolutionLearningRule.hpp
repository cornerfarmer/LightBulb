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
	class AbstractIndividual;
	class AbstractEvolutionEnvironment;
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
	/**
	 * \brief All events the EvolutionLearningRule can throw.
	 */
	enum EvolutionLearningEvents
	{
		/**
		 * \brief Is thrown after every evolution step.
		 */
		EVT_EL_EVOLUTIONSTEP
	};
	/**
	* \brief All options for the evolution learning rule.
	*/
	struct EvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
	{
		/**
		 * \brief A few conditions which evaluate if the learning process should be stopped.
		 */
		std::vector<AbstractExitCondition*> exitConditions;
		/**
		 * \brief Commands for creating new individuals.
		 */
		std::vector<AbstractCreationCommand*> creationCommands;
		/**
		 * \brief Commands for selecting individuals which should stay.
		 */
		std::vector<AbstractSelectionCommand*> selectionCommands;
		/**
		 * \brief Functions which can modify the calculated fitness values.
		 */
		std::vector<AbstractFitnessFunction*> fitnessFunctions;
		/**
		 * \brief Commands for mutating those individuals.
		 */
		std::vector<AbstractMutationCommand*> mutationsCommands;
		/**
		 * \brief Commands for combining two individuals to a new one
		 */
		std::vector<AbstractRecombinationCommand*> recombinationCommands;
		/**
		 * \brief Commands for directly reusing individuals.
		 */
		std::vector<AbstractReuseCommand*> reuseCommands;
		/**
		* \brief Creates the options and fills them with default options.
		*/
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
	/**
	 * \brief Describes a learning rule which uses evolution to train neural networks.
	 */
	class EvolutionLearningRule : public AbstractEvolutionLearningRule, public Observable<EvolutionLearningEvents, EvolutionLearningRule>
	{
		template <class Archive>
		friend void serialize(Archive& archive, EvolutionLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<EvolutionLearningRule>;
	protected:
		/**
		 * \brief Contains all individuals which are currently not in use and can be reused.
		 */
		std::vector<AbstractIndividual*> notUsedIndividuals;
		/**
		 * \brief True, if the exit condition has been reached.
		 */
		bool exitConditionReached;
		// Inherited:
		void doIteration() override;
		bool hasLearningSucceeded() override;
		const EvolutionLearningRuleOptions& getOptions() const;
		void doCalculationAfterLearningProcess() override;
		void setHelperToUsedObjects() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		/**
		* \brief Creates the coevolution learning rule.
		* \param options_ The options which configure the coevolution learning rule.
		*/
		EvolutionLearningRule(EvolutionLearningRuleOptions& options_);
		/**
		* \brief Creates the coevolution learning rule.
		* \param options_ The options which configure the coevolution learning rule.
		*/
		EvolutionLearningRule(EvolutionLearningRuleOptions* options_);
		EvolutionLearningRule();
		/**
		* \brief Returns the name of the learning rule
		* \return The name
		*/
		static std::string getName();
		// Inherited:
		void initializeTry() override;
		std::vector<std::string> getDataSetLabels() const override;
		void setLogger(AbstractLogger& logger) override;
	};
}

#include "IO/EvolutionLearningRuleIO.hpp"

#endif
