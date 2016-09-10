#pragma once

#ifndef _FITNESSSHARINGFITNESSFUNCTION_H_
#define _FITNESSSHARINGFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class FitnessSharingFitnessFunction : public AbstractFitnessFunction
	{
	private:
		double exponent;
		double dissimilarityThreshold;
	public:
		FitnessSharingFitnessFunction(double dissimilarityThreshold_, double exponent_ = 1);
		//
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) override;
	};
}

#endif
