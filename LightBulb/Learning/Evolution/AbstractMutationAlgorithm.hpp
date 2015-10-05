#pragma once

#ifndef _ABSTRACTMUTATIONALGORITHM_H_
#define _ABSTRACTMUTATIONALGORITHM_H_

// Library Includes
#include <memory>

// Forward declarations
class AbstractEvolutionObject;

class AbstractMutationAlgorithm
{
public:
	virtual void execute(AbstractEvolutionObject* object1) = 0;
};

#endif