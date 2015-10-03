// Includes
#include "Learning\Evolution\BestSelectionCommand.hpp"
#include "Learning\Evolution\AbstractEvolutionWorld.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
//Library includes
#include <iostream>
#include <iomanip>

BestSelectionCommand::BestSelectionCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void BestSelectionCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
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
