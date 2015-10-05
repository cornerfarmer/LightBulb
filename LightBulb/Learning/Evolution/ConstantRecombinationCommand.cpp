// Includes
#include "Learning\Evolution\ConstantRecombinationCommand.hpp"
#include "Learning\Evolution\AbstractEvolutionWorld.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
#include "Learning\Evolution\EvolutionLearningRule.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, int objectCount_)
	: AbstractRecombinationCommand(recombinationAlgorithm_)
{
	objectCount = objectCount_;
}

void ConstantRecombinationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	std::cout << "Recombinated " << objectCount << " random ones" << std::endl;
	
	int entryIndex = 0;
	for (int i = 0; i < objectCount; i++)
	{
		int recombinationnIndex1 = rankBasedRandomFunction.execute(highscore->size());
		int recombinationnIndex2 = rankBasedRandomFunction.execute(highscore->size());
		newObjectVector->push_back((*highscore)[recombinationnIndex1].second->clone());
		AbstractEvolutionObject* secondClone = (*highscore)[recombinationnIndex2].second->clone();
		recombinationAlgorithm->execute(newObjectVector->back(), secondClone);
	}

}
