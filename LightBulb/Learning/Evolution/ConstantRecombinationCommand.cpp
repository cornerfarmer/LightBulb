// Includes
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

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

void ConstantRecombinationCommand::select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * recombinationPercentage);
	recombinationSelector->executeRecombinationSelection(objectCount, highscore, counter);
}

void ConstantRecombinationCommand::setRecombinationPercentage(double newRecombinationPercentage)
{
	recombinationPercentage = newRecombinationPercentage;
}
