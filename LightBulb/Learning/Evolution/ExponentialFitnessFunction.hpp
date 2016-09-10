#pragma once

#ifndef _EXPONENTIALFITNESSFUNCTION_H_
#define _EXPONENTIALFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class ExponentialFitnessFunction : public AbstractFitnessFunction
	{
	private:
		double exponent;
		double proportionalScaling;
		double base;
	public:
		ExponentialFitnessFunction(double exponent_ = 1.005, double proportionalScaling_ = 1, double base_ = 0);
		//
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) override;
	};
}

#endif
