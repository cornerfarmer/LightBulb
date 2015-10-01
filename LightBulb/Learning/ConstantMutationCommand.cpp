// Includes
#include "Learning\ConstantMutationCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
#include "Learning\EvolutionLearningRule.hpp"
//Library includes
#include <iostream>

ConstantMutationCommand::ConstantMutationCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void ConstantMutationCommand::execute(EvolutionLearningRule* learningRule, std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector)
{
	std::cout << "Mutated " << objectCount << " random ones" << std::endl;
	
	int entryIndex = 0;
	for (int i = 0; i < objectCount; i++)
	{
		int mutationIndex = rankBasedRandomFunction.execute(highscore->size());
		newObjectVector->push_back((*highscore)[mutationIndex].second->clone());
		learningRule->doMutation(*newObjectVector->back());
	}
}
