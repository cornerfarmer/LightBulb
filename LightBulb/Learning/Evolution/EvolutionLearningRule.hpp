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

struct EvolutionLearningRuleOptions
{
	std::vector<AbstractExitCondition*> exitConditions;
	std::vector<AbstractCreationCommand*> creationCommands;
	std::vector<AbstractSelectionCommand*> selectionCommands;
	std::vector<AbstractMutationCommand*> mutationsCommands;
	std::vector<AbstractRecombinationCommand*> recombinationCommands;
	std::vector<AbstractReuseCommand*> reuseCommands;
	AbstractEvolutionWorld* world;
	bool enableDebugOutput;
	double scoreGoal;
	int maxTries;
	EvolutionLearningRuleOptions()
	{
		world = NULL;
		enableDebugOutput = false;
		scoreGoal = 0;
		maxTries = 1;
	}
};


class EvolutionLearningRule 
{
protected:
	std::unique_ptr<EvolutionLearningRuleOptions> options;
	
public:	
	EvolutionLearningRule(EvolutionLearningRuleOptions& options_);
	void doMutation(AbstractEvolutionObject& object);
	AbstractEvolutionObject* doRecombination(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2);
	LearningResult doLearning();
	EvolutionLearningRuleOptions* getOptions();
};

#endif
