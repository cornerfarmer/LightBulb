#pragma once

#ifndef _EXAMPLETRAININGPLAN_H_
#define _EXAMPLETRAININGPLAN_H_

// Includes
#include "Teaching/AbstractTrainingPlan.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class ExampleTrainingPlan : public AbstractTrainingPlan
{
private:
	void run();
public:
	std::string getName();
	std::string getDescription();
	std::string getLearningRateName();
	AbstractTrainingPlan* getCopy();
};

#endif
