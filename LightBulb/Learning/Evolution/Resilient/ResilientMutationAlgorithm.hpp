#pragma once

#ifndef _RESILIENTMUTATIONALGORITHM_H_
#define _RESILIENTMUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"

// Forward declarations
class AbstractEvolutionObject;

// A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm
class ResilientMutationAlgorithm : public AbstractMutationAlgorithm
{
private:
	int focusedEdgeIndex;
	int direction;
public:
	ResilientMutationAlgorithm();
	// Mutates the given evolution object:
	// 1. Changes the mutationStrength values randomly
	// 2. Adds the new mutationStrength values to their corresponding weights
	void execute(AbstractEvolutionObject* object1);
	void setFocusedEdgeIndex(int newFocusedEdgeIndex);
	void setDirection(int newDirection);
};

#endif
