#pragma once

#ifndef _TEACHINGEVOLUTIONWORLD_H_
#define _TEACHINGEVOLUTIONWORLD_H_

// Library Includes
#include <vector>
#include <map>
// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class Teacher;

class TeachingEvolutionWorld : public AbstractSimpleEvolutionWorld
{
protected:
	AbstractEvolutionObject* createNewObject();
	Teacher* teacher;
	LayeredNetworkOptions networkOptions;
public:
	TeachingEvolutionWorld(Teacher* teacher_, LayeredNetworkOptions& networkOptions_);
	void doSimulationStep(EvolutionLearningRule& learningRule);
	double getScore(AbstractEvolutionObject* object);
	Teacher* getTeacher();
};

#endif
