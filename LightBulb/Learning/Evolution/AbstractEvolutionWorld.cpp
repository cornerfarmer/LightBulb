// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>
#include <functional>

std::vector<std::pair<double, AbstractEvolutionObject*>>* AbstractEvolutionWorld::getHighscoreList()
{
	// Create new vector which should return the whole highscore
	currentHighscore.reset(new std::vector<std::pair<double, AbstractEvolutionObject*>>(getPopulationSize()));
	// Go through all evolution objects
	int listIndex = 0;
	for (auto object = getEvolutionObjects()->begin(); object < getEvolutionObjects()->end(); object++)
	{		
		double score = getScore(*object);

		// Add the objects paired with its score to the list
		(*currentHighscore)[listIndex++] = std::make_pair(score, *object);

	}
	// Sort the list
	std::sort(currentHighscore->begin(), currentHighscore->end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
	return currentHighscore.get();
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
