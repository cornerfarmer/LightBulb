// Includes
#include "Learning/Evolution/ConstantMutationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
//Library includes
#include <iostream>
#include <stdexcept>

ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_,  int objectCount_, bool enableDebugOutput_)
	: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_, enableDebugOutput_)
{
	objectCount = objectCount_;
	mutationPercentage = 0;
}

ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_,  double mutationPercentage_, bool enableDebugOutput_)
	: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_, enableDebugOutput_)
{
	mutationPercentage = mutationPercentage_;
	objectCount = 0;
}


void ConstantMutationCommand::select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * mutationPercentage);

	mutationSelector->executeMutationSelection(objectCount, highscore, counter);
}

void ConstantMutationCommand::setMutationPercentage(double newMutationPercentage)
{
	mutationPercentage = newMutationPercentage;
}
