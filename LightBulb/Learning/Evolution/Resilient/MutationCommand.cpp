// Includes
#include <Learning/Evolution/Resilient/ResilientMutationAlgorithm.hpp>
#include "Learning/Evolution/Resilient/MutationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>
#include <iomanip>

MutationCommand::MutationCommand()
	: AbstractMutationCommand(new ResilientMutationAlgorithm(), true)
{

}


void MutationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{


	// Do N times
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		for (auto mutationStrength = entry->second->getMutationStrength()->begin(); mutationStrength != entry->second->getMutationStrength()->end();mutationStrength++)
		{
			std::cout << std::fixed << std::setprecision(5) << *mutationStrength << ", ";
		}
		std::cout << std::endl;

		int edgeCount = entry->second->getNeuralNetwork()->getNetworkTopology()->getEdgeCount();
		for (int d = -1; d <= 1; d+= 2)
		{
			static_cast<ResilientMutationAlgorithm*>(mutationAlgorithm.get())->setDirection(d);
			for (int i = 0; i < edgeCount; i++)
			{
				// Clone it and add it to the new object vector
				newObjectVector->push_back(entry->second->clone());
				static_cast<ResilientMutationAlgorithm*>(mutationAlgorithm.get())->setFocusedEdgeIndex(i);
				// Mutate the new object
				mutationAlgorithm->execute(newObjectVector->back());

				(*newObjectVector->back()->getMutationStrength())[i] = std::min(50.0, (*newObjectVector->back()->getMutationStrength())[i] * 5);
			}
		}
		newObjectVector->push_back(entry->second->clone());
		for (int i = 0; i < edgeCount; i++)
			(*newObjectVector->back()->getMutationStrength())[i] = std::max(0.0, (*newObjectVector->back()->getMutationStrength())[i] / 2);
	}
}
