#pragma once

#ifndef _ABSTRACTRECOMBINATION_H_
#define _ABSTRACTRECOMBINATION_H_

// Library Includes

// Includes

// Forward declarations
class EvolutionObjectInterface;

class AbstractRecombination
{
private:
public:
	virtual void execute(EvolutionObjectInterface* object1, EvolutionObjectInterface* object2) = 0;
};

#endif