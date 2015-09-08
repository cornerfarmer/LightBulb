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

struct EvolutionLearningRuleOptions
{
	std::vector<AbstractCreationCommand*> creationCommands;
	std::vector<AbstractSelectionCommand*> selectionCommands;
	std::vector<AbstractMutationCommand*> mutationsCommands;
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
	EvolutionObjectInterface* doRecombination(std::vector<EvolutionObjectInterface*> object);

	bool doLearning(EvolutionWorldInterface& world);
};

#endif