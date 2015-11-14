// Includes
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_, bool enableDebugOutput_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_, enableDebugOutput_)
{
	objectCount = objectCount_;
	recombinationPercentage = 0;
}

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_, bool enableDebugOutput_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_, enableDebugOutput_)
{
	objectCount = 0;
	recombinationPercentage = recombinationPercentage_;
}

void ConstantRecombinationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * recombinationPercentage);

	if (enableDebugOutput)
		std::cout << "Recombinated " << objectCount << " random ones" << std::endl;
	
	if (highscore->size() > 0)
	{
		recombinationSelector->initRecombination(highscore, objectCount);

		int entryIndex = 0;
		// Do N times
		for (int i = 0; i < objectCount; i++)
		{
			// Select two random objects
			std::array<AbstractEvolutionObject*, 2> chosenObjects = recombinationSelector->nextRecombination();
			// Clone the first objects and add it to the new object vector
			newObjectVector->push_back(chosenObjects[0]->clone());
			// Also clone the second object
			AbstractEvolutionObject* secondClone = chosenObjects[01]->clone();
			// Combine the two objects
			recombinationAlgorithm->execute(newObjectVector->back(), secondClone);

			delete(secondClone);
		}

		if (!recombinationSelector->hasFinished())
			throw std::logic_error("The recombinationSelector has not finished properly!");
	}
}

void ConstantRecombinationCommand::setRecombinationPercentage(double newRecombinationPercentage)
{
	recombinationPercentage = newRecombinationPercentage;
}
