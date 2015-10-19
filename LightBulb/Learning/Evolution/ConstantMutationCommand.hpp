#pragma once

#ifndef _CONSTANTMUTATIONCOMMAND_H_
#define _CONSTANTMUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

// Forward declarations


class ConstantMutationCommand : public AbstractMutationCommand
{
private:
	int objectCount;
	double mutationPercentage;
	RankBasedRandomFunction rankBasedRandomFunction;
public:
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, int objectCount_, bool enableDebugOutput_ = false);
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, double mutationPercentage_, bool enableDebugOutput_ = false);
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
	void setMutationPercentage(double newMutationPercentage);
};

#endif
