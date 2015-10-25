#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

// A command which selects a few of the existing evolution objects, which will be forwarded to the mutation, recombination and reuse commands.
class AbstractSelectionCommand
{
protected:
	bool enableDebugOutput;
public:
	virtual ~AbstractSelectionCommand() {};
	AbstractSelectionCommand(bool enableDebugOutput_);
	// The command will delete all not-selected objects from the vector.
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
};

#endif
