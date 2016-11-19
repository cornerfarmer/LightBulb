// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>
#include <functional>

namespace LightBulb
{
	AbstractEvolutionWorld::AbstractEvolutionWorld()
	{
		recalculateHighscore = true;
	}

	Highscore& AbstractEvolutionWorld::getHighscoreList()
	{
		if (recalculateHighscore)
		{
			currentHighscore.clear();
			// Go through all individuals
			for (auto individual = getIndividuals().begin(); individual < getIndividuals().end(); individual++)
			{
				double score = getScore(**individual);

				// Add the individuals paired with its score to the list
				currentHighscore.push_back(std::make_pair(score, *individual));

			}
			// Sort the list
			sort(currentHighscore.begin(), currentHighscore.end(), std::greater<std::pair<double, AbstractIndividual*>>());
			recalculateHighscore = false;
		}
		return currentHighscore;
	}

	std::vector<std::string> AbstractEvolutionWorld::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}

	void AbstractEvolutionWorld::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}

	void AbstractEvolutionWorld::refreshHighscore()
	{
		recalculateHighscore = true;
	}
}