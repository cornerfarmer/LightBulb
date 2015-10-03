#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Include
#include "Learning\AbstractRecombination.hpp"

// Library Includes
#include <vector>

// Forward declarations
class EvolutionObjectInterface;
class EvolutionWorldInterface;
class EvolutionLearningRule;

class AbstractRecombinationCommand
{
protected:
	std::unique_ptr<AbstractRecombination> recombination;
public:
	AbstractRecombinationCommand(AbstractRecombination* recombination_);
	virtual void execute(std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector) = 0;
};

#endif