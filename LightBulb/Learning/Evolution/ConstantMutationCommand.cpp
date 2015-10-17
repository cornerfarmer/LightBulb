// Includes
#include "Learning/Evolution/ConstantMutationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
//Library includes
#include <iostream>

ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, int objectCount_, bool enableDebugOutput_)
	: AbstractMutationCommand(mutationAlgorithm_, enableDebugOutput_)
{
	objectCount = objectCount_;
}

ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, double mutationPercentage_, bool enableDebugOutput_)
	: AbstractMutationCommand(mutationAlgorithm_, enableDebugOutput_)
{
	mutationPercentage = mutationPercentage_;
	objectCount = 0;
}

void ConstantMutationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * mutationPercentage);

	if (enableDebugOutput)
		std::cout << "Mutated " << objectCount << " random ones" << std::endl;
	
	int entryIndex = 0;
	for (int i = 0; i < objectCount; i++)
	{
		int mutationIndex = rankBasedRandomFunction.execute(highscore->size());
		newObjectVector->push_back((*highscore)[mutationIndex].second->clone());
		mutationAlgorithm->execute(newObjectVector->back());
	}
}
