// Includes
#include "Learning\Evolution\ConstantMutationCommand.hpp"
#include "Learning\Evolution\AbstractEvolutionWorld.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
#include "Learning\Evolution\EvolutionLearningRule.hpp"
//Library includes
#include <iostream>

ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, int objectCount_)
	: AbstractMutationCommand(mutationAlgorithm_)
{
	objectCount = objectCount_;
}

void ConstantMutationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	std::cout << "Mutated " << objectCount << " random ones" << std::endl;
	
	int entryIndex = 0;
	for (int i = 0; i < objectCount; i++)
	{
		int mutationIndex = rankBasedRandomFunction.execute(highscore->size());
		newObjectVector->push_back((*highscore)[mutationIndex].second->clone());
		mutationAlgorithm->execute(newObjectVector->back());
	}
}
