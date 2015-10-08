// Includes
#include "Learning\Evolution\BestSelectionCommand.hpp"
#include "Learning\Evolution\AbstractEvolutionWorld.hpp"
#include "Learning\Evolution\AbstractEvolutionObject.hpp"
#include "Learning\Evolution\EvolutionLearningRule.hpp"
//Library includes
#include <iostream>
#include <iomanip>
#include <algorithm>

BestSelectionCommand::BestSelectionCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void BestSelectionCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	std::cout << "Selected " << objectCount << " best ones:";
	
	if (highscore->size() > objectCount)
	{
		for (auto entry = highscore->begin() + objectCount; entry != highscore->end(); entry++)
		{
			delete(entry->second);
		}

		highscore->resize(objectCount);
	}
		
	std::cout << std::endl;
}
