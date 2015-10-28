// Includes
#include "Learning/Evolution/BestAICountCondition.hpp"
#include "Examples/TicTacToe.hpp"
// Library includes
#include <vector>

bool BestAICountCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	return world->getBestAIs()->size() > count;
}

BestAICountCondition::BestAICountCondition(TicTacToe* world_, int count_, bool enableDebugOutput_)
	: AbstractExitCondition(enableDebugOutput_)
{
	world = world_;
	count = count_;
}
