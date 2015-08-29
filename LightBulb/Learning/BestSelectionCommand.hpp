#pragma once

#ifndef _BESTSELECTIONCOMMAND_H_
#define _BESTSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning\AbstractSelectionCommand.hpp"

// Forward declarations


class BestSelectionCommand : public AbstractSelectionCommand
{
private:
	int objectCount;
public:
	BestSelectionCommand(int objectCount_);
	void execute(EvolutionWorldInterface& world);
};

#endif