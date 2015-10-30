#pragma once

#ifndef _MUTATIONCOMMAND_H_
#define _MUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

// Forward declarations

// Mutates a constant amount of objects
class MutationCommand : public AbstractMutationCommand
{
private:

public:
	virtual ~MutationCommand() {};
		// Creates a command which mutates a static amount of objects
	MutationCommand();
		// Takes N objects, mutates them and adds them to the new objects vector
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
