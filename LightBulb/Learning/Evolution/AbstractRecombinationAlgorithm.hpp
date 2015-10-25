#pragma once

#ifndef _ABSTRACTRECOMBINATIONALGORITHM_H_
#define _ABSTRACTRECOMBINATIONALGORITHM_H_

// Library Includes

// Includes

// Forward declarations
class AbstractEvolutionObject;

// A algorithm which describes the recombination of two existing evolution objects into a new one.
class AbstractRecombinationAlgorithm
{
private:
public:
	virtual ~AbstractRecombinationAlgorithm() {};
	// This method combines the two given objects to a new one which will be stored inside the first given object.
	virtual void execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2) = 0;
};

#endif
