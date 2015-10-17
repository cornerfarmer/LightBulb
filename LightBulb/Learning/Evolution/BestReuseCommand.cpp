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
}

void BestReuseCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	if (enableDebugOutput)
		std::cout << "Reuse " << objectCount << " best one:";
	
	int entryIndex = 0;
	for (auto entry = highscore->begin(); entry != highscore->end() && entryIndex < objectCount; entry++, entryIndex++)
	{
		newObjectVector->push_back(entry->second->clone());
		if (enableDebugOutput)
			std::cout << std::fixed << std::setprecision(7) << entry->first << ", ";
	}

	if (enableDebugOutput)
		std::cout << std::endl;
}
