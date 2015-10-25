#pragma once

#ifndef _ABSTRACTMUTATIONALGORITHM_H_
#define _ABSTRACTMUTATIONALGORITHM_H_

// Library Includes
#include <memory>

// Forward declarations
class AbstractEvolutionObject;

// A algorithm which mutates the given object.
class AbstractMutationAlgorithm
{
public:
	virtual ~AbstractMutationAlgorithm() {};
	// Mutates the given evolution object.
	virtual void execute(AbstractEvolutionObject* object1) = 0;
};

#endif
