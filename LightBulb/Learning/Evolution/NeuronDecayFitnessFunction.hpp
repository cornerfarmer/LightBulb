#pragma once

#ifndef _NEURONDECAYFITNESSFUNCTION_H_
#define _NEURONDECAYFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

// Forward declarations

//
class NeuronDecayFitnessFunction : public AbstractFitnessFunction
{
private:
	double fac;
public:
	NeuronDecayFitnessFunction(double fac_);
	//
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) override;
};

#endif
