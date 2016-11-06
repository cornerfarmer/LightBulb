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
			// Go through all evolution objects
			for (auto object = getEvolutionObjects().begin(); object < getEvolutionObjects().end(); object++)
			{
				double score = getScore(**object);

				// Add the objects paired with its score to the list
				currentHighscore.push_back(std::make_pair(score, *object));

			}
			// Sort the list
			sort(currentHighscore.begin(), currentHighscore.end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
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