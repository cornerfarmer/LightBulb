#pragma once

#ifndef _WEIGHTDECAYFITNESSFUNCTION_H_
#define _WEIGHTDECAYFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class WeightDecayFitnessFunction : public AbstractFitnessFunction
	{
	private:
		double fac;
	public:
		WeightDecayFitnessFunction(double fac_);
		//
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	};
}

#endif
