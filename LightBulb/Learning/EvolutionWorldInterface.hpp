#pragma once

#ifndef _EVOLUTIONWORLDINTERFACE_H_
#define _EVOLUTIONWORLDINTERFACE_H_

// Library Includes


// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;

class EvolutionWorldInterface 
{
public:
	virtual EvolutionObjectInterface* addNewObject() = 0;
	virtual void doSimulationStep(EvolutionLearningRule& learningRule) = 0;
};

#endif