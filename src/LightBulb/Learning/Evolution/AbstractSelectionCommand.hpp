#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

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
	 * \brief A command that selects a few of the evolution objects which will be forwarded to the mutation, recombination and reuse commands.
	 */
	class AbstractSelectionCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractSelectionCommand() {}
		/**
		 * \brief The command will delete all not-selected objects from the vector.
		 * \param highscore The highscore.
		 * \param objects A vector where all selected objects will be stored in.
		 * \param notUsedObjects A vector where all not selected objects will be stored in.
		 */
		virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::vector<AbstractEvolutionObject*>& objects, std::vector<AbstractEvolutionObject*>& notUsedObjects) = 0;
	};
}

#endif
