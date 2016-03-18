#pragma once

#ifndef _EVOLUTIONLEARNINGRULE_H_
#define _EVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/LearningResult.hpp"

// Library Includes
#include <vector>
#include <memory>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class AbstractCreationCommand;
class AbstractSelectionCommand;
class AbstractMutationCommand;
class AbstractRecombinationCommand;
class AbstractExitCondition;
class AbstractReuseCommand;
class AbstractFitnessFunction;

struct EvolutionLearningRuleOptions
{
	// Holds a few conditions which evaluate if the learning process should be stopped
	std::vector<AbstractExitCondition*> exitConditions;
	// Holds commands for creating new objects
	std::vector<AbstractCreationCommand*> creationCommands;
	// Holds commands for selecting objects which should stay
	std::vector<AbstractSelectionCommand*> selectionCommands;
	// Holds function which can modify the calculated fitness values
	std::vector<AbstractFitnessFunction*> fitnessFunctions;
	// Holds commands for mutating those objects
	std::vector<AbstractMutationCommand*> mutationsCommands;
	// Holds commands for combining two objects into a new one
	std::vector<AbstractRecombinationCommand*> recombinationCommands;
	// Holds commands for directly reusing objects
	std::vector<AbstractReuseCommand*> reuseCommands;
	// The world which should contain all trained evolution objects
	AbstractEvolutionWorld* world;
	// Enable debugging output
	bool enableDebugOutput;
	// Holds the score which should be reached after the learning process
	double scoreGoal;
	// The maximum tries which can be used to reach the score goal
	int maxTries;
	EvolutionLearningRuleOptions()
	{
		world = NULL;
		enableDebugOutput = false;
		scoreGoal = 0;
		maxTries = 1;
	}
};

// A learingRule for improving NNs with the help of algorithms oriented by the evolution
class EvolutionLearningRule
{
protected:
	std::unique_ptr<EvolutionLearningRuleOptions> options;
	int generation;
	std::vector<AbstractEvolutionObject*> notUsedObjects;
public:
	EvolutionLearningRule(EvolutionLearningRuleOptions& options_);
	EvolutionLearningRuleOptions* getOptions();
	// Executes the learning process
	LearningResult doLearning();
	bool doEvolutionStep();
	void initialize();
	// TODO: Remove/Move into own classes
	void doMutation(AbstractEvolutionObject& object);
	AbstractEvolutionObject* doRecombination(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2);
};

#endif
