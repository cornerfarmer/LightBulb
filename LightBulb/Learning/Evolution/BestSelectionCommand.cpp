// Includes
#include "Learning/Evolution/BestSelectionCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
//Library includes
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace LightBulb
{
	BestSelectionCommand::BestSelectionCommand(int objectCount_)
		: AbstractSelectionCommand()
	{
		objectCount = objectCount_;
		selectionPercentage = 0;
	}

	BestSelectionCommand::BestSelectionCommand(double selectionPercentage_)
		: AbstractSelectionCommand()
	{
		objectCount = 0;
		selectionPercentage = selectionPercentage_;
	}

	void BestSelectionCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::vector<AbstractEvolutionObject*>& objects, std::vector<AbstractEvolutionObject*>& notUsedObjects)
	{
		int objectCount = this->objectCount;
		// Calculate a temporary static object count if the percentage value is used
		if (selectionPercentage)
			objectCount = highscore.size() * selectionPercentage;

		if (highscore.size() > objectCount)
		{
			objects.clear();

			for (auto entry = highscore.begin(); entry != highscore.begin() + objectCount; entry++)
			{
				objects.push_back(entry->second);
			}

			// Go through all not selected objects
			for (auto entry = highscore.begin() + objectCount; entry != highscore.end(); entry++)
			{
				// Recycle them
				notUsedObjects.push_back(entry->second);
			}

			// Resize the vector
			highscore.resize(objectCount);
		}


		double totalFitness = 0;
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			totalFitness += entry->first;
		}
		log("Selected " + std::to_string(objectCount) + " best ones. Average: " + std::to_string(static_cast<double>(totalFitness) / highscore.size()), LL_LOW);

	}

	AbstractCloneable* BestSelectionCommand::clone() const
	{
		return new BestSelectionCommand(*this);
	}

	void BestSelectionCommand::setObjectCount(int newObjectCount)
	{
		objectCount = newObjectCount;
	}
}