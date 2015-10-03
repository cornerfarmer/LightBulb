#pragma once

#ifndef _FUNCTIONSIMULATOR_H_
#define _FUNCTIONSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Learning\Evolution\AbstractSimpleEvolutionWorld.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class AbstractTile;

class FunctionSimulator : public AbstractSimpleEvolutionWorld
{
protected:
	AbstractEvolutionObject* createNewObject();
public:
	FunctionSimulator();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	double getScore(AbstractEvolutionObject* object);
};

#endif