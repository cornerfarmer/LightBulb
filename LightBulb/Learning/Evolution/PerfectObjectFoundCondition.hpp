#pragma once

#ifndef _PERFECTOBJECTFOUNDCONDITION_H_
#define _PERFECTOBJECTFOUNDCONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

// Forward declarations
class AbstractCombiningStrategy;

// A condition which matches if the best score only changes under a specified number for a chosen time
class PerfectObjectFoundCondition : public AbstractExitCondition
{
private:
	AbstractCombiningStrategy* combiningStrategy;
	// Counts how many times the difference was lower than the allowed minimum
	int counter;
	// Holds the time for how long the score must be lower than the allow minimum
	int count;
	bool perfectObjectExists();
public:
	void setCount(int newCount);
	// Creates a new condition with the minimum difference and the allowed timesteps
	PerfectObjectFoundCondition(int count_, AbstractCombiningStrategy* combiningStrategy_, bool enableDebugOutput_ = false);
	// Inherited:
	bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
