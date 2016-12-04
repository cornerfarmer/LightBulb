#pragma once

#ifndef _ABSTRACTMUTATIONCOMMAND_H_
#define _ABSTRACTMUTATIONCOMMAND_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractMutationSelector.hpp"

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Learning/Evolution/AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class AbstractEvolutionEnvironment;
	class EvolutionLearningRule;
	/**
	 * \brief A command which mutates a few of the given individuals.
	 */
	class AbstractMutationCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief The algorithm which executes the mutations.
		 */
		std::unique_ptr<AbstractMutationAlgorithm> mutationAlgorithm;
		/**
		 * \brief The algorithm which selects individuals for mutation.
		 */
		std::unique_ptr<AbstractMutationSelector> mutationSelector;
	public:
		virtual ~AbstractMutationCommand() {}
		AbstractMutationCommand() = default;
		AbstractMutationCommand(const AbstractMutationCommand& other);
		/**
		 * \brief Creates a new mutation command.
		 * \param mutationAlgorithm_ The mutation algorithm to use.
		 * \param mutationSelector_ The mutation selector to use.
		 */
		AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_);
		friend void swap(AbstractMutationCommand& lhs, AbstractMutationCommand& rhs) noexcept;
		/**
		 * \brief Select individuals for mutation.
		 * \param highscore The current highscore.
		 * \param counter A counter which stores how often an individual is used in all commands.
		 */
		virtual void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) = 0;
		/**
		 * \brief Executes the mutations.
		 * \details The algorithm will take a few of the old individuals, mutate them and insert them into the new individual vector
		 * \param newIndividualVector A vector where the new/mutated individuals will be stored in.
		 * \param counter A counter of all left operations per individual.
		 * \param notUsedIndividuals A vector of individuals which are not used anymore.
		 */
		virtual void execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals);
		virtual void setZigguratGenerator(ZigguratGenerator& generator);
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
