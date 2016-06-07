// Includes
#include "Learning/Evolution/BipartiteEvolutionLearningRule.hpp"
// Library includes
#include <iostream>


AbstractLearningResult* BipartiteEvolutionLearningRule::getLearningResult()
{
	return getOptions()->learningRule1->getLearningResult();
}

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
	std::vector<std::string> labels1 = getOptions()->learningRule1->getDataSetLabels();
	std::vector<std::string> labels2 = getOptions()->learningRule2->getDataSetLabels();
	labels1.insert(labels1.end(), labels2.begin(), labels2.end());
	return labels1;
}

AbstractEvolutionLearningRule* BipartiteEvolutionLearningRule::getFirstLearningRule()
{
	return getOptions()->learningRule1;
}


AbstractEvolutionLearningRule* BipartiteEvolutionLearningRule::getSecondLearningRule()
{
	return getOptions()->learningRule2;
}


void BipartiteEvolutionLearningRule::initialize()
{
	exitConditionReached = false;
	getOptions()->learningRule1->learningState = learningState;
	getOptions()->learningRule2->learningState = learningState;
	getOptions()->learningRule1->setLogger(options->logger);
	getOptions()->learningRule2->setLogger(options->logger);
}

BipartiteEvolutionLearningRuleOptions* BipartiteEvolutionLearningRule::getOptions()
{
	return static_cast<BipartiteEvolutionLearningRuleOptions*>(options.get());
}

bool BipartiteEvolutionLearningRule::doIteration()
{
	log("lr1: ", LL_MEDIUM);
	bool successfull = getOptions()->learningRule1->doIteration();
	learningState->iterations--;
	if (!successfull) {
		exitConditionReached = true;
		return false;
	}

	log("lr2: ", LL_MEDIUM);
	getOptions()->learningRule2->doIteration();
	learningState->iterations--;
	return true;
}

void BipartiteEvolutionLearningRule::initializeTry()
{
	getOptions()->learningRule1->initializeTry();
	getOptions()->learningRule2->initializeTry();
}

bool BipartiteEvolutionLearningRule::hasLearningSucceeded()
{
	return exitConditionReached;
}
