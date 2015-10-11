#pragma once

#ifndef _ABSTRACTEVOLUTIONWORLD_H_
#define _ABSTRACTEVOLUTIONWORLD_H_

// Library Includes
#include <vector>
#include <memory>

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;

class AbstractEvolutionWorld
{

public:
	virtual AbstractEvolutionObject* addNewObject() = 0;
	virtual void doSimulationStep(EvolutionLearningRule& learningRule) = 0;
	virtual std::vector<AbstractEvolutionObject*>* getEvolutionObjects() = 0;
	virtual void setEvolutionObjects(std::vector<AbstractEvolutionObject*>& newObjects) = 0;
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> getHighscoreList();
	virtual double getScore(AbstractEvolutionObject* object) = 0;
	virtual void reset() = 0;
};

#endif
