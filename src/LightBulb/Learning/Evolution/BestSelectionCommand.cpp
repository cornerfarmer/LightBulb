// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/BestSelectionCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
//Library includes

namespace LightBulb
{
	BestSelectionCommand::BestSelectionCommand(int individualCount_)
		: AbstractSelectionCommand()
	{
		individualCount = individualCount_;
		selectionPercentage = 0;
	}

	BestSelectionCommand::BestSelectionCommand(double selectionPercentage_)
		: AbstractSelectionCommand()
	{
		individualCount = 0;
		selectionPercentage = selectionPercentage_;
	}

	void BestSelectionCommand::execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::vector<AbstractIndividual*>& individuals, std::vector<AbstractIndividual*>& notUsedIndividuals)
	{
		int individualCount = this->individualCount;
		// Calculate a temporary static individual count if the percentage value is used
		if (selectionPercentage)
			individualCount = highscore.size() * selectionPercentage;

		if (highscore.size() > individualCount)
		{
			individuals.clear();

			for (auto entry = highscore.begin(); entry != highscore.begin() + individualCount; entry++)
			{
				individuals.push_back(entry->second);
			}

			// Go through all not selected individuals
			for (auto entry = highscore.begin() + individualCount; entry != highscore.end(); entry++)
			{
				// Recycle them
				notUsedIndividuals.push_back(entry->second);
			}

			// Resize the vector
			highscore.resize(individualCount);
		}


		double totalFitness = 0;
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			totalFitness += entry->first;
		}
		log("Selected " + std::to_string(individualCount) + " best ones. Average: " + std::to_string(static_cast<double>(totalFitness) / highscore.size()), LL_LOW);

	}

	AbstractCloneable* BestSelectionCommand::clone() const
	{
		return new BestSelectionCommand(*this);
	}
}