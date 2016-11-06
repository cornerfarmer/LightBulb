#pragma once

#ifndef _POSITIVEMAKERFITNESSFUNCTION_H_
#define _POSITIVEMAKERFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class PositiveMakerFitnessFunction : public AbstractFitnessFunction
	{
	private:
		double constant;
	public:
		PositiveMakerFitnessFunction(double constant_);
		//
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;

		AbstractFitnessFunction* clone() const override;
	};
}

#endif
