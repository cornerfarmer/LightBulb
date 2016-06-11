#pragma once

#ifndef _MOCKEVOLUTIONLEARNINGRULE_H_
#define _MOCKEVOLUTIONLEARNINGRULE_H_

#include "gmock/gmock.h"
#include <Learning/AbstractEvolutionLearningRule.hpp>

class MockEvolutionLearningRule : public AbstractEvolutionLearningRule
{
public:
	MockEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_):AbstractEvolutionLearningRule(options_) {};
	MOCK_METHOD0(doIteration, bool ());
	MOCK_METHOD0(getWorld, AbstractEvolutionWorld* ());
	MOCK_METHOD0(initializeStartLearningAlgoritm, void ());
	MOCK_METHOD0(initializeResumeLearningAlgoritm, void ());
	MOCK_METHOD0(initializeLearningAlgoritm, void ());
	MOCK_METHOD0(initializeTry, void ());
	MOCK_METHOD0(doCalculationAfterLearningProcess, void ());
	MOCK_METHOD0(rateLearning, void ());
	MOCK_METHOD0(hasLearningSucceeded, bool ());
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_METHOD0(getLearningResult, AbstractLearningResult* ());
	MOCK_METHOD1(fillDefaultResults, void (AbstractLearningResult*));
};

#endif
