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

	// A command which reuses a few of the given evolution objects directly.
	class AbstractReuseCommand : public AbstractCommand
	{
	protected:
		//
		std::unique_ptr<AbstractReuseSelector> reuseSelector;
	public:
		virtual ~AbstractReuseCommand() {};
		AbstractReuseCommand() = default;
		AbstractReuseCommand(AbstractReuseSelector* reuseSelector_);
		AbstractReuseCommand(const AbstractReuseCommand& other);
		friend void swap(AbstractReuseCommand& lhs, AbstractReuseCommand& rhs) noexcept;

		// Execute the command (Take a few of the old objects and move them directly into the new object vector)
		virtual void execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects);
		virtual void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) = 0;
	};
}

#endif
