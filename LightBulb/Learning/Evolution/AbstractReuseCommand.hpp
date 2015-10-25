#pragma once

#ifndef _ABSTRACTREUSECOMMAND_H_
#define _ABSTRACTREUSECOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;

// A command which reuses a few of the given evolution objects directly.
class AbstractReuseCommand
{
protected:
	bool enableDebugOutput;
public:
	virtual ~AbstractReuseCommand() {};
	AbstractReuseCommand(bool enableDebugOutput_);
	// Execute the command (Take a few of the old objects and move them directly into the new object vector)
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector) = 0;
};

#endif
