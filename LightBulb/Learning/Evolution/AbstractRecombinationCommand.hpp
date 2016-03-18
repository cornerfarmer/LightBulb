#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Include
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"

// Library Includes
#include <vector>
#include <memory>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

// A command which combines a few of the given evolution objects.
class AbstractRecombinationCommand
{
protected:
	// Holds the chosen recombination algorithm
	std::unique_ptr<AbstractRecombinationAlgorithm> recombinationAlgorithm;
	//
	std::unique_ptr<AbstractRecombinationSelector> recombinationSelector;
	bool enableDebugOutput;
public:
	virtual ~AbstractRecombinationCommand() {};

	virtual void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter) = 0;
	// Create a new recombination command with the given recombination algorithm
	AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_,  bool enableDebugOutput_);
	// Executes the recombinations. (The algorithm will take a few of the old objects, combine them and insert the created ones into the new object vector)
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter, std::vector<AbstractEvolutionObject*>* notUsedObjects);
};

#endif
