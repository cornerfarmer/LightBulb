#pragma once

#ifndef _ABSTRACTREUSECOMMAND_H_
#define _ABSTRACTREUSECOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;

class AbstractReuseCommand
{
public:
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector) = 0;
};

#endif