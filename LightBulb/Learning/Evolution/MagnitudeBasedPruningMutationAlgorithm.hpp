#pragma once

#ifndef _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_
#define _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include <Function/RankBasedRandomFunction.hpp>

// Forward declarations
class AbstractEvolutionObject;

// A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm
class MagnitudeBasedPruningMutationAlgorithm : public AbstractMutationAlgorithm
{
private:
	RankBasedRandomFunction randomFunction;
	int removeNeuronsPerIteration;
	int removeWeightsPerIteration;
	bool removeNeuronsByTheirTotalWeight;
public:
	MagnitudeBasedPruningMutationAlgorithm(int removeNeuronsPerIteration_, int removeWeightsPerIteration_, bool removeNeuronsByTheirTotalWeight_ = false);

	void execute(AbstractEvolutionObject* object1);
};

#endif
