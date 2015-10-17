#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Include
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"

// Library Includes
#include <vector>
#include <memory>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

class AbstractRecombinationCommand
{
protected:
	std::unique_ptr<AbstractRecombinationAlgorithm> recombinationAlgorithm;
	bool enableDebugOutput;
public:
	AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, bool enableDebugOutput_);
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector) = 0;
};

#endif
