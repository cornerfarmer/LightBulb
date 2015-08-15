// Includes
#include "Learning\EvolutionLearningRule.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\AbstractCreationCommand.hpp"

EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions& options_)
{
	options.reset(new EvolutionLearningRuleOptions(options_));
}

void EvolutionLearningRule::doMutation(EvolutionObjectInterface& object)
{

}

EvolutionObjectInterface* EvolutionLearningRule::doRecombination(std::vector<EvolutionObjectInterface*> object)
{
	return NULL;
}

bool EvolutionLearningRule::doLearning(EvolutionWorldInterface& world)
{
	for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
	{
		(*creationCommand)->execute(world);
	}

	world.doSimulationStep(*this);

	return true;
}