#pragma once

#ifndef _MUTATIONALGORITHM_H_
#define _MUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "Random/ZigguratGenerator.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	// A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm
	class MutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		// This factor influences the change speed of mutationStrengths
		double mutationStrengthChangeSpeed;
		// The absolute minimum of a mutationStrength value
		double mutationStrengthMin;
		// The absolute maximum of a mutationStrength value
		double mutationStrengthMax;
		ZigguratGenerator generator;
	public:
		MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_ = 50, double mutationStrengthMin_ = 0.000001f);
		void setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_);
		// Mutates the given evolution object:
		// 1. Changes the mutationStrength values randomly
		// 2. Adds the new mutationStrength values to their corresponding weights
		void execute(AbstractEvolutionObject& object1) override;
		AbstractMutationAlgorithm* clone() const override;
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
