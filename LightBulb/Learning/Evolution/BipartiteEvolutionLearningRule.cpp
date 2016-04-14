// Includes
#include "Learning/Evolution/BipartiteEvolutionLearningRule.hpp"
// Library includes
#include <iostream>


BipartiteEvolutionLearningRule::BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions& options_)
	: AbstractEvolutionLearningRule(new BipartiteEvolutionLearningRuleOptions(options_))
{
	initialize();
}

BipartiteEvolutionLearningRule::BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions* options_)
	: AbstractEvolutionLearningRule(options_)
{
	initialize();
}

std::string BipartiteEvolutionLearningRule::getName()
{
	return "BipartiteEvolutionLearningRule";
}

std::vector<std::string> BipartiteEvolutionLearningRule::getDataSetLabels()
{
	return AbstractEvolutionLearningRule::getDataSetLabels();
}

void BipartiteEvolutionLearningRule::initialize()
{
	getOptions()->learningRule1->options->logger = options->logger;
	getOptions()->learningRule2->options->logger = options->logger;
	getOptions()->learningRule1->setLoggerToUsedObjects();
	getOptions()->learningRule2->setLoggerToUsedObjects();
	getOptions()->learningRule1->learningState.reset(learningState.get());
	getOptions()->learningRule2->learningState.reset(learningState.get());
}

BipartiteEvolutionLearningRuleOptions* BipartiteEvolutionLearningRule::getOptions()
{
	return static_cast<BipartiteEvolutionLearningRuleOptions*>(options.get());
}

bool BipartiteEvolutionLearningRule::doIteration()
{
	getOptions()->learningRule1->iteration = iteration;
	getOptions()->learningRule2->iteration = iteration;
	getOptions()->learningRule1->tryCounter = tryCounter;
	getOptions()->learningRule2->tryCounter = tryCounter;
	log("lr1: ", LL_MEDIUM);
	bool successfull = getOptions()->learningRule1->doIteration();
	if (!successfull)
		return false;
	log("lr2: ", LL_MEDIUM);
	getOptions()->learningRule2->doIteration();
	return true;
}

void BipartiteEvolutionLearningRule::initializeTry()
{
	getOptions()->learningRule1->initializeTry();
	getOptions()->learningRule2->initializeTry();
}

bool BipartiteEvolutionLearningRule::hasLearningSucceeded()
{
	return tryCounter > 1;
}
