// Includes
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, int objectCount_, bool enableDebugOutput_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, enableDebugOutput_)
{
	objectCount = objectCount_;
	recombinationPercentage = 0;
}

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, double recombinationPercentage_, bool enableDebugOutput_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, enableDebugOutput_)
{
	objectCount = 0;
	recombinationPercentage = recombinationPercentage_;
}

void ConstantRecombinationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	int objectCount = this->objectCount;
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * recombinationPercentage);

	if (enableDebugOutput)
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
