#pragma once

#ifndef _BESTREUSECOMMAND_H_
#define _BESTREUSECOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"

// Forward declarations


class BestReuseCommand : public AbstractReuseCommand
{
private:
	int objectCount;
public:
	BestReuseCommand(int objectCount_);
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif