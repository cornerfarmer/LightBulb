#pragma once

#ifndef _RECOMBINATIONALGORITHM_H_
#define _RECOMBINATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"

// Forward declarations
class AbstractEvolutionObject;

// A algorithm which combines two given evolution objects by executing the corresponding EvolutionStrategy algorithm
class RecombinationAlgorithm : public AbstractRecombinationAlgorithm
{
private:
public:
	// The algorithm calculates a simple average between the two given objects.
	void execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2);
};

#endif
