// Includes
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
//Library include
#include <algorithm>
#include <functional>

namespace LightBulb
{
	AbstractEvolutionEnvironment::AbstractEvolutionEnvironment()
	{
		recalculateHighscore = true;
	}

	bool AbstractEvolutionEnvironment::pairCompare(const std::pair<double, AbstractIndividual*>& firstElem, const std::pair<double, AbstractIndividual*>& secondElem) {
		return firstElem.first > secondElem.first;
	}

	Highscore& AbstractEvolutionEnvironment::getHighscoreList()
	{
		if (recalculateHighscore)
		{
			currentHighscore.clear();
			// Go through all individuals
			for (auto individual = getIndividuals().begin(); individual < getIndividuals().end(); individual++)
			{
				double fitness = getFitness(**individual);

				// Add the individuals paired with its fitness to the list
				currentHighscore.push_back(std::make_pair(fitness, *individual));

			}
			// Sort the list
			//std::random_shuffle(currentHighscore.begin(), currentHighscore.end());
			//std::stable_sort(currentHighscore.begin(), currentHighscore.end(), pairCompare);
			sort(currentHighscore.begin(), currentHighscore.end(), std::greater<std::pair<double, AbstractIndividual*>>());
			recalculateHighscore = false;
		}
		return currentHighscore;
	}

	std::vector<std::string> AbstractEvolutionEnvironment::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}

	void AbstractEvolutionEnvironment::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}

	void AbstractEvolutionEnvironment::refreshHighscore()
	{
		recalculateHighscore = true;
	}
}