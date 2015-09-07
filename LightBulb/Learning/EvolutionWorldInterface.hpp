#pragma once

#ifndef _EVOLUTIONWORLDINTERFACE_H_
#define _EVOLUTIONWORLDINTERFACE_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;

class EvolutionWorldInterface 
{

public:
	virtual EvolutionObjectInterface* addNewObject() = 0;
	virtual void doSimulationStep(EvolutionLearningRule& learningRule) = 0;
	virtual std::vector<EvolutionObjectInterface*>* getEvolutionObjects() = 0;
	virtual void setEvolutionObjects(std::vector<EvolutionObjectInterface*>& newObjects) = 0;
	std::unique_ptr<std::vector<std::pair<double, EvolutionObjectInterface*>>> getHighscoreList();
	virtual int getScore(EvolutionObjectInterface* object) = 0;
	virtual void reset() = 0;
};

#endif