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
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	/**
	 * \brief A command which reuses a few of the given evolution objects directly.
	 */
	class AbstractReuseCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief All selected objects.
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
		 * \details Takes a few of the old objects and moves them directly into the new object vector.
		 * \param newObjectVector A vector where the reused objects will be stored in.
		 * \param counter A counter of all left operations per object.
		 * \param notUsedObjects A vector of objects which are not used anymore.
		 */
		virtual void execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects);
		/**
		* \brief Select objects for reusing.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an object is used in all commands.
		*/
		virtual void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) = 0;
	};
}

#endif
