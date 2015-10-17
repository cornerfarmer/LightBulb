#pragma once

#ifndef _ABSTRACTEXITCONDITION_H_
#define _ABSTRACTEXITCONDITION_H_

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;

class AbstractExitCondition
{
protected:
	bool enableDebugOutput;
public:
	AbstractExitCondition(bool enableDebugOutput_);
	virtual bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
};

#endif
