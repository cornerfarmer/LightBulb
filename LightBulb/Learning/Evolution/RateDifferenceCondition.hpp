#pragma once

#ifndef _RATEDIFFERENCECONDITION_H_
#define _RATEDIFFERENCECONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

// Forward declarations

// A condition which matches if the best score only changes under a specified number for a chosen time
class RateDifferenceCondition : public AbstractExitCondition
{
private:
	// Holds the best score of the last generation
	double lastBestRate;
	// Holds the minimum allowed difference
	double difference;
	// Counts how many times the difference was lower than the allowed minimum
	int counter;
	// Holds the time for how long the score must be lower than the allow minimum
	int count;
public:
	virtual ~RateDifferenceCondition() {}
	void setCount(int newCount);
	// Creates a new condition with the minimum difference and the allowed timesteps
	RateDifferenceCondition(double difference_, int count_, bool enableDebugOutput_ = false);
	// Inherited:
	bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
