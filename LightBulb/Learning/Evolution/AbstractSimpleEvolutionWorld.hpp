#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLD_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLD_H_

// Library Includes
#include <vector>

// Include
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;

class AbstractSimpleEvolutionWorld : public AbstractEvolutionWorld
{
protected:
	std::vector<AbstractEvolutionObject*> objects;
	virtual AbstractEvolutionObject* createNewObject() = 0;
	virtual void resetWorld() {};
public:
	AbstractSimpleEvolutionWorld();
	AbstractEvolutionObject* addNewObject();
	std::vector<AbstractEvolutionObject*>* getEvolutionObjects();
	void setEvolutionObjects(std::vector<AbstractEvolutionObject*>& newObjects);
	void reset();	
};

#endif