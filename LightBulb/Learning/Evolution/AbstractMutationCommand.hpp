#pragma once

#ifndef _ABSTRACTMUTATIONCOMMAND_H_
#define _ABSTRACTMUTATIONCOMMAND_H_

// Includes
#include "Learning\Evolution\AbstractMutationAlgorithm.hpp"

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

class AbstractMutationCommand
{
protected:
	std::unique_ptr<AbstractMutationAlgorithm> mutationAlgorithm;
public:
	AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_);
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector) = 0;
};

#endif