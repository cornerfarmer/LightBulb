#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Include
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	class EvolutionLearningRule;
	/**
	 * \brief A command which recombines a few of the given evolution objects.
	 */
	class AbstractRecombinationCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief The algorithm which executes the recombination.
		 */
		std::unique_ptr<AbstractRecombinationAlgorithm> recombinationAlgorithm;
		/**
		 * \brief The algorithm which selects objects for recombination.
		 */
		std::unique_ptr<AbstractRecombinationSelector> recombinationSelector;
	public:
		virtual ~AbstractRecombinationCommand() {}
		AbstractRecombinationCommand() = default;
		AbstractRecombinationCommand(const AbstractRecombinationCommand& other);
		friend void swap(AbstractRecombinationCommand& lhs, AbstractRecombinationCommand& rhs) noexcept;
		/**
		 * \brief Creates a new recombination command.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 */
		AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_);
		/**
		* \brief Select objects for recombination.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an object is used in all commands.
		*/
		virtual void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) = 0;
		/**
		* \brief Executes the recombination.
		* \details The algorithm will take a few of the old objects, recombine them and insert them into the new object vector
		* \param newObjectVector A vector where the new/recombinated objects will be stored in.
		* \param counter A counter of all left operations per object.
		* \param notUsedObjects A vector of objects which are not used anymore.
		*/
		virtual void execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects);
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
