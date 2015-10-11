#pragma once

#ifndef _BESTSELECTIONCOMMAND_H_
#define _BESTSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSelectionCommand.hpp"

// Forward declarations

class BestSelectionCommand : public AbstractSelectionCommand
{
private:
	int objectCount;
public:
	BestSelectionCommand(int objectCount_);
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif