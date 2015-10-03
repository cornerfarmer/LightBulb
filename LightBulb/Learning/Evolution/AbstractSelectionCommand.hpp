#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;

class AbstractSelectionCommand
{
public:
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector) = 0;
};

#endif