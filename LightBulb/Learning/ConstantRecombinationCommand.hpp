#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning\AbstractRecombinationCommand.hpp"
#include "Function\RankBasedRandomFunction.hpp"

// Forward declarations


class ConstantRecombinationCommand : public AbstractRecombinationCommand
{
private:
	int objectCount;
	RankBasedRandomFunction rankBasedRandomFunction;
public:
	ConstantRecombinationCommand(int objectCount_);
	void execute(EvolutionLearningRule* learningRule, std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector);
};

#endif