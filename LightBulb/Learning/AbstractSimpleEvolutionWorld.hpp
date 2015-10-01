#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLD_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLD_H_

// Library Includes
#include <vector>

// Include
#include "Learning\EvolutionWorldInterface.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;

class AbstractSimpleEvolutionWorld : public EvolutionWorldInterface
{
protected:
	std::vector<EvolutionObjectInterface*> objects;
	virtual EvolutionObjectInterface* createNewObject() = 0;
	virtual void resetWorld() {};
public:
	AbstractSimpleEvolutionWorld();
	EvolutionObjectInterface* addNewObject();
	std::vector<EvolutionObjectInterface*>* getEvolutionObjects();
	void setEvolutionObjects(std::vector<EvolutionObjectInterface*>& newObjects);
	void reset();	
};

#endif