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
	virtual void removeEvolutionObject(EvolutionObjectInterface* evolutionObject) = 0;
	virtual EvolutionObjectInterface* getEvolutionObject(int index) = 0;
	virtual bool isBetterThan(EvolutionObjectInterface* first, EvolutionObjectInterface* second) = 0;
	virtual int getEvolutionObjectCount() = 0;
	virtual void reset() = 0;
};

#endif