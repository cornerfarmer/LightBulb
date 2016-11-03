#pragma once

#ifndef _ABSTRACTMUTATIONCOMMAND_H_
#define _ABSTRACTMUTATIONCOMMAND_H_

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractMutationSelector.hpp"

// Library Includes
#include <vector>

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	class EvolutionLearningRule;
	/**
	 * \brief A command which mutates a few of the given evolution objects.
	 */
	class AbstractMutationCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief The algorithm which executes the mutations.
		 */
		std::unique_ptr<AbstractMutationAlgorithm> mutationAlgorithm;
		/**
		 * \brief The algorithm which selects objects for mutation.
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
		 * \brief Select objects for mutation.
		 * \param highscore The current highscore.
		 * \param counter A counter which stores how often an object is used in all commands.
		 */
		virtual void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) = 0;
		/**
		 * \brief Executes the mutations.
		 * \details The algorithm will take a few of the old objects, mutate them and insert them into the new object vector
		 * \param newObjectVector A vector where the new/mutated objects will be stored in.
		 * \param counter A counter of all left operations per object.
		 * \param notUsedObjects A vector of objects which are not used anymore.
		 */
		virtual void execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects);
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
