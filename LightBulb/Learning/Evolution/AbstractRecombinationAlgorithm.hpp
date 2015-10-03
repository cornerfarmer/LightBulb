#pragma once

#ifndef _ABSTRACTRECOMBINATIONALGORITHM_H_
#define _ABSTRACTRECOMBINATIONALGORITHM_H_

// Library Includes

// Includes

// Forward declarations
class AbstractEvolutionObject;

class AbstractRecombinationAlgorithm
{
private:
public:
	virtual void execute(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2) = 0;
};

#endif