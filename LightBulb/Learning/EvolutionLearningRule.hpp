#pragma once

#ifndef _EVOLUTIONLEARNINGRULE_H_
#define _EVOLUTIONLEARNINGRULE_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionObjectInterface;
class EvolutionWorldInterface;
class AbstractCreationCommand;
class AbstractSelectionCommand;
class AbstractMutationCommand;
class AbstractRecombinationCommand;

struct EvolutionLearningRuleOptions
{
	std::vector<AbstractCreationCommand*> creationCommands;
	std::vector<AbstractSelectionCommand*> selectionCommands;
	std::vector<AbstractMutationCommand*> mutationsCommands;
	std::vector<AbstractRecombinationCommand*> recombinationCommands;
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
	void doMutation(EvolutionObjectInterface& object);
	EvolutionObjectInterface* doRecombination(EvolutionObjectInterface* object1, EvolutionObjectInterface* object2);

	bool doLearning(EvolutionWorldInterface& world);
};

#endif