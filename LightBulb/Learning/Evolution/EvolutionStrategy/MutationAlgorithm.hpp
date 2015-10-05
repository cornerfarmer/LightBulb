#pragma once

#ifndef _MUTATIONALGORITHM_H_
#define _MUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning\Evolution\AbstractMutationAlgorithm.hpp"

// Forward declarations
class AbstractEvolutionObject;

class MutationAlgorithm : public AbstractMutationAlgorithm
{
private:
public:
	void execute(AbstractEvolutionObject* object1);
};

#endif