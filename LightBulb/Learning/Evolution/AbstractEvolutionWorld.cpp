// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>
#include <functional>

Highscore* AbstractEvolutionWorld::getHighscoreList()
{
	currentHighscore.clear();
	// Go through all evolution objects
	for (auto object = getEvolutionObjects()->begin(); object < getEvolutionObjects()->end(); object++)
	{		
		double score = getScore(*object);

		// Add the objects paired with its score to the list
		currentHighscore.push_back(std::make_pair(score, *object));

	}
	// Sort the list
	std::sort(currentHighscore.begin(), currentHighscore.end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
	return &currentHighscore;
}

std::vector<std::string> AbstractEvolutionWorld::getDataSetLabels()
{
	std::vector<std::string> labels;
	return labels;
}

void AbstractEvolutionWorld::setLearningState(LearningState* learningState_)
{
	learningState = learningState_;
}
