// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>
#include <functional>

bool AbstractEvolutionWorld::compareHighscoreEntries(const std::pair<double, AbstractEvolutionObject*>& x, const std::pair<double, AbstractEvolutionObject*>& y)
{
	return x.first > y.first || (x.first == y.first && rand() > RAND_MAX / 2);
}

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
