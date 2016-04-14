// Includes
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
{
	setRecombinationCount(objectCount_);
}

ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_)
	: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
{
	setRecombinationPercentage(recombinationPercentage_);
}

void ConstantRecombinationCommand::select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * recombinationPercentage);
	recombinationSelector->executeRecombinationSelection(objectCount, highscore, counter);
}

void ConstantRecombinationCommand::setRecombinationPercentage(double newRecombinationPercentage)
{
	objectCount = 0;
	recombinationPercentage = newRecombinationPercentage;
}

void ConstantRecombinationCommand::setRecombinationCount(int newObjectCount)
{
	recombinationPercentage = 0;
	objectCount = newObjectCount;
}
