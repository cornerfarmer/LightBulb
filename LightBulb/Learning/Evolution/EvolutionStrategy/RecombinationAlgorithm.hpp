#pragma once

#ifndef _RECOMBINATIONALGORITHM_H_
#define _RECOMBINATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning\Evolution\AbstractRecombinationAlgorithm.hpp"

// Forward declarations
class AbstractEvolutionObject;

class RecombinationAlgorithm : public AbstractRecombinationAlgorithm
{
private:
public:
	void execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2);
};

#endif