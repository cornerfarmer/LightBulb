#pragma once

#ifndef _STANDARDDEVIATIONFITNESSFUNCTION_H_
#define _STANDARDDEVIATIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

// Forward declarations

//
class StandardDeviationFitnessFunction : public AbstractFitnessFunction
{
private:
	double deviationFac;
public:
	StandardDeviationFitnessFunction(double deviationFac_ = 0);
	//
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
