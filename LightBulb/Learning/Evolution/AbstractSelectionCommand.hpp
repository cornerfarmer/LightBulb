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

	// A command which selects a few of the existing evolution objects, which will be forwarded to the mutation, recombination and reuse commands.
	class AbstractSelectionCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractSelectionCommand() {}
		// The command will delete all not-selected objects from the vector.
		virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::vector<AbstractEvolutionObject*>& objects, std::vector<AbstractEvolutionObject*>& notUsedObjects) = 0;
	};
}

#endif
