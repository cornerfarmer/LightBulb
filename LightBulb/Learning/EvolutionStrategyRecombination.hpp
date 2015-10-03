#pragma once

#ifndef _EVOLUTIONSTRATEGYRECOMBINATION_H_
#define _EVOLUTIONSTRATEGYRECOMBINATION_H_

// Library Includes

// Includes
#include "Learning\AbstractRecombination.hpp"

// Forward declarations
class EvolutionObjectInterface;

class EvolutionStrategyRecombination : public AbstractRecombination
{
private:
public:
	void execute(EvolutionObjectInterface* object1, EvolutionObjectInterface* object2);
};

#endif