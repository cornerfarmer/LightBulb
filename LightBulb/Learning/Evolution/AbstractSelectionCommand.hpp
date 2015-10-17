#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

class AbstractSelectionCommand
{
protected:
	bool enableDebugOutput;
public:
	AbstractSelectionCommand(bool enableDebugOutput_);
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
};

#endif
