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

void ConstantMutationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * mutationPercentage);

	if (enableDebugOutput)
		std::cout << "Mutated " << objectCount << " random ones" << std::endl;
	
	if (highscore->size() > 0)
	{
		mutationSelector->initMutation(highscore, objectCount);

		int entryIndex = 0;
		// Do N times
		for (int i = 0; i < objectCount; i++)
		{
			// Select a random object
			AbstractEvolutionObject* chosenObject = mutationSelector->nextMutation();
			// Clone it and add it to the new object vector
			newObjectVector->push_back(chosenObject->clone());
			// Mutate the new object
			mutationAlgorithm->execute(newObjectVector->back());
		}

		if (!mutationSelector->hasFinished())
			throw std::logic_error("The mutationSelector has not finished properly!");
	}
}

void ConstantMutationCommand::setMutationPercentage(double newMutationPercentage)
{
	mutationPercentage = newMutationPercentage;
}
