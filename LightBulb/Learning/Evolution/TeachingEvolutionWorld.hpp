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
class AbstractTeacher;

#define DATASET_TEACHING_ERROR "Teaching error"
#define DATASET_WEIGHTDECAY_ERROR "Weigth decay error"

// Evolution world which can be used to use the EvolutionLearingRule in combination with a Teacher
class TeachingEvolutionWorld : public AbstractSimpleEvolutionWorld
{
protected:
	// Inherited
	AbstractEvolutionObject* createNewObject();
	// Holds the given teacher
	AbstractTeacher* teacher;
	// Holds the given network options for new evolution objects
	LayeredNetworkOptions networkOptions;
public:
	// Creates a new world with the given teacher and the network options
	TeachingEvolutionWorld(AbstractTeacher* teacher_, LayeredNetworkOptions& networkOptions_);
	AbstractTeacher* getTeacher();
	// Inherited:
	bool doSimulationStep();
	std::vector<std::string> getDataSetLabels();
	double getScore(AbstractEvolutionObject* object);
};

#endif
