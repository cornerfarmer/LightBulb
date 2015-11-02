#pragma once

#ifndef _ABSTRACTEVOLUTIONWORLD_H_
#define _ABSTRACTEVOLUTIONWORLD_H_

// Library Includes
#include <vector>
#include <memory>

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;

// This class should describe a world which contains multiple evolution objects.
// The evolution world has to simulate the environment which surrounds its evolution objects.
class AbstractEvolutionWorld
{
private:
	static bool compareHighscoreEntries(const std::pair<double, AbstractEvolutionObject*>& x, const std::pair<double, AbstractEvolutionObject*>& y);
public:
	virtual ~AbstractEvolutionWorld() {};
	virtual std::vector<AbstractEvolutionObject*>* getEvolutionObjects() = 0;
	virtual void setEvolutionObjects(std::vector<AbstractEvolutionObject*>& newObjects) = 0;
	// This method should create a new evolution object and add it to the world
	virtual AbstractEvolutionObject* addNewObject(bool addToWorld = true) = 0;
	// This method should execute one simulation step.
	// After each simulation step the evolution learning rule will execute each evolution command (selection, mutation, recombination...)
	virtual void doSimulationStep(EvolutionLearningRule& learningRule) = 0;
	// Returns a list of all current evolution objects ordered by their score
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> getHighscoreList();
	// This method should calculate the score of the given evolution object (TODO: Rename score to fitness)
	virtual double getScore(AbstractEvolutionObject* object) = 0;
	// Reset the whole world (This method can for instance reset the environment or the current evolution objects...)
	virtual void reset() = 0;
};

#endif
