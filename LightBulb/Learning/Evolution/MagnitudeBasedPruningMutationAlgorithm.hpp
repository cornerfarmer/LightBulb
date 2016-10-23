#pragma once

#ifndef _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_
#define _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include <Function/RandomFunction/EqualRandomFunction.hpp>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	// A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm
	class MagnitudeBasedPruningMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		EqualRandomFunction randomFunction;
		int removeNeuronsPerIteration;
		int removeWeightsPerIteration;
		bool removeNeuronsByTheirTotalWeight;
		bool useRandomFunction;
		bool ignoreInputLayer;
	public:
		MagnitudeBasedPruningMutationAlgorithm(int removeNeuronsPerIteration_, int removeWeightsPerIteration_, bool useRandomFunction_ = true, bool ignoreInputLayer_ = false, bool removeNeuronsByTheirTotalWeight_ = false);

		void execute(AbstractEvolutionObject& object1) override;

		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
