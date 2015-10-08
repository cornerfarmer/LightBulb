#pragma once

#ifndef _EVOLUTIONLEARNINGRULE_H_
#define _EVOLUTIONLEARNINGRULE_H_

// Library Includes
#include <vector>

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
	EvolutionLearningRuleOptions()
	{

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
	bool doLearning(AbstractEvolutionWorld& world);
};

#endif