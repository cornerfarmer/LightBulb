// Includes
#include "Learning/Evolution/BipartiteEvolutionLearningRule.hpp"
// Library includes
#include <iostream>

BipartiteEvolutionLearningRule::BipartiteEvolutionLearningRule(EvolutionLearningRule* learningRule1_, EvolutionLearningRule* learningRule2_)
{
	learningRule1 = learningRule1_;
	learningRule2 = learningRule2_;
}

LearningState BipartiteEvolutionLearningRule::doLearning()
{
	learningRule1->initialize();
	learningRule2->initialize();

	bool stopLearning = false;
	while (!stopLearning) {
		stopLearning = false;
		std::cout << "lr1: ";
		stopLearning |= learningRule1->doEvolutionStep();
		if (stopLearning)
			break;
		std::cout << "lr2: ";
		stopLearning |= learningRule2->doEvolutionStep();
	}
	LearningState result;
	return result;
}