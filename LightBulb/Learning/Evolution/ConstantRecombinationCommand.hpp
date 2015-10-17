#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

// Forward declarations


class ConstantRecombinationCommand : public AbstractRecombinationCommand
{
private:
	int objectCount;
	double recombinationPercentage;
	RankBasedRandomFunction rankBasedRandomFunction;
public:
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, int objectCount_, bool enableDebugOutput_ = false);
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, double recombinationPercentage_, bool enableDebugOutput_ = false);
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
