#pragma once

#ifndef _ABSTRACTEXITCONDITION_H_
#define _ABSTRACTEXITCONDITION_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionObjectInterface;

class AbstractExitCondition
{
public:
	virtual bool evaluate(std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore) = 0;
};

#endif