#pragma once

#ifndef _LINEARSSCALINGFITNESSFUNCTION_H_
#define _LINEARSCALINGFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class LinearScalingFitnessFunction : public AbstractFitnessFunction
	{
	private:
		double proportionalScaling;
		double base;
		bool useDynamicScaling;
	public:
		LinearScalingFitnessFunction(double proportionalScaling_, double base_, bool useDynamicScaling_ = false);
		//
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	};
}

#endif
