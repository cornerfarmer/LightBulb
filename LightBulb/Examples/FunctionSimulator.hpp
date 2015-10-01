#pragma once

#ifndef _FUNCTIONSIMULATOR_H_
#define _FUNCTIONSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Learning\AbstractSimpleEvolutionWorld.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;
class AbstractTile;

class FunctionSimulator : public AbstractSimpleEvolutionWorld
{
protected:
	EvolutionObjectInterface* createNewObject();
public:
	FunctionSimulator();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	double getScore(EvolutionObjectInterface* object);
};

#endif