// Includes
#include "Learning\ConstantRecombinationCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
#include "Learning\EvolutionLearningRule.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombination* recombination, int objectCount_)
	: AbstractRecombinationCommand(recombination)
{
	objectCount = objectCount_;
}

void ConstantRecombinationCommand::execute(std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector)
{
	std::cout << "Recombinated " << objectCount << " random ones" << std::endl;
	
	int entryIndex = 0;
	for (int i = 0; i < objectCount; i++)
	{
		int recombinationnIndex1 = rankBasedRandomFunction.execute(highscore->size());
		int recombinationnIndex2 = rankBasedRandomFunction.execute(highscore->size());
		newObjectVector->push_back((*highscore)[recombinationnIndex1].second->clone());
		EvolutionObjectInterface* secondClone = (*highscore)[recombinationnIndex2].second->clone();
		recombination->execute(newObjectVector->back(), secondClone);
	}

}
