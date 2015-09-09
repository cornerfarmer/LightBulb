#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionObjectInterface;
class EvolutionWorldInterface;
class EvolutionLearningRule;

class AbstractRecombinationCommand
{
public:
	virtual void execute(EvolutionLearningRule* learningRule, std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector) = 0;
};

#endif