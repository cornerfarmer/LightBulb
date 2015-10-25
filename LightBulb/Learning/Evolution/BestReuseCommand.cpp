// Includes
#include "Learning/Evolution/BestReuseCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <iostream>
#include <iomanip>

BestReuseCommand::BestReuseCommand(int objectCount_, bool enableDebugOutput_)
	: AbstractReuseCommand(enableDebugOutput_)
{
	objectCount = objectCount_;
	reusePercentage = 0;
}

BestReuseCommand::BestReuseCommand(double reusePercentage_, bool enableDebugOutput_)
	: AbstractReuseCommand(enableDebugOutput_)
{
	objectCount = 0;
	reusePercentage = reusePercentage_;
}

void BestReuseCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	int objectCount = this->objectCount;
	// Calculate a temporary static object count if the percentage value is used
	if (objectCount == 0)
		objectCount = (int)(highscore->size() * reusePercentage);

	if (enableDebugOutput)
		std::cout << "Reuse " << objectCount << " best one:";
	
	// Go through all old objects
	int entryIndex = 0;
	for (auto entry = highscore->begin(); entry != highscore->end() && entryIndex < objectCount; entry++, entryIndex++)
	{
		// Move the object to the new vector
		newObjectVector->push_back(entry->second->clone());
		if (enableDebugOutput)
			std::cout << std::fixed << std::setprecision(7) << entry->first << ", ";
	}

	if (enableDebugOutput)
		std::cout << std::endl;
}
