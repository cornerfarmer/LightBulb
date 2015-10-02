// Includes
#include "Learning\BestSelectionCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
//Library includes
#include <iostream>
#include <iomanip>

BestSelectionCommand::BestSelectionCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void BestSelectionCommand::execute(std::vector<std::pair<double, EvolutionObjectInterface*>>* highscore, std::vector<EvolutionObjectInterface*>* newObjectVector)
{
	std::cout << "Selected " << objectCount << " best one:";
	
	int entryIndex = 0;
	for (auto entry = highscore->begin(); entry != highscore->end() && entryIndex < objectCount; entry++, entryIndex++)
	{
		newObjectVector->push_back(entry->second->clone());
		std::cout << std::fixed << std::setprecision(7) << entry->first << ", ";
	}

	std::cout << std::endl;
}
