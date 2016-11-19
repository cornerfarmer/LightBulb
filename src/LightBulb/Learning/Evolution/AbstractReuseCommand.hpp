#pragma once

#ifndef _ABSTRACTREUSECOMMAND_H_
#define _ABSTRACTREUSECOMMAND_H_

// Library Includes
#include <vector>
#include <map>
#include <memory>

// Includes
#include "AbstractReuseSelector.hpp"
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class AbstractEvolutionWorld;
	/**
	 * \brief A command which reuses a few of the given individuals directly.
	 */
	class AbstractReuseCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief All selected individuals.
		 */
		std::unique_ptr<AbstractReuseSelector> reuseSelector;
	public:
		virtual ~AbstractReuseCommand() {};
		AbstractReuseCommand() = default;
		AbstractReuseCommand(AbstractReuseSelector* reuseSelector_);
		AbstractReuseCommand(const AbstractReuseCommand& other);
		friend void swap(AbstractReuseCommand& lhs, AbstractReuseCommand& rhs) noexcept;
		/**
		 * \brief Executes the command.
		 * \details Takes a few of the old individuals and moves them directly into the new individual vector.
		 * \param newIndividualVector A vector where the reused individuals will be stored in.
		 * \param counter A counter of all left operations per individual.
		 * \param notUsedIndividuals A vector of individuals which are not used anymore.
		 */
		virtual void execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals);
		/**
		* \brief Select individuals for reusing.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an individual is used in all commands.
		*/
		virtual void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) = 0;
	};
}

#endif
