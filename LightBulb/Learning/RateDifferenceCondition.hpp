#pragma once

#ifndef _RATEDIFFERENCECONDITION_H_
#define _RATEDIFFERENCECONDITION_H_

// Includes
#include "Learning\AbstractExitCondition.hpp"

// Forward declarations

class RateDifferenceCondition : public AbstractExitCondition
{
private:
	double lastBestRate;
	double differnce;
	int counter;
	int count;
public:
	RateDifferenceCondition(double differnce_, int count_);
	bool evaluate(std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore);
};

#endif