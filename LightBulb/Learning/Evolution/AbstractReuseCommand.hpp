#pragma once

#ifndef _ABSTRACTREUSECOMMAND_H_
#define _ABSTRACTREUSECOMMAND_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "AbstractReuseSelector.hpp"

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;

// A command which reuses a few of the given evolution objects directly.
class AbstractReuseCommand
{
protected:
	//
	std::unique_ptr<AbstractReuseSelector> reuseSelector;

	bool enableDebugOutput;
public:
	virtual ~AbstractReuseCommand() {};
	AbstractReuseCommand(AbstractReuseSelector* reuseSelector_, bool enableDebugOutput_);
	// Execute the command (Take a few of the old objects and move them directly into the new object vector)
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
	virtual void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter) = 0 ;
};

#endif
