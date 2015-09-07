// Includes
#include "Learning\BestSelectionCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
//Library includes
#include <iostream>

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
		newObjectVector->push_back(entry->second);
		std::cout << (int)entry->first << ", ";		
	}

	std::cout << std::endl;
}
