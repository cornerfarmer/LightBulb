#pragma once

#ifndef _MOCKEVOLUTIONLEARNINGRULE_H_
#define _MOCKEVOLUTIONLEARNINGRULE_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionLearningRule.hpp>
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/AbstractLearningResult.hpp"

class MockEvolutionLearningRule : public LightBulb::AbstractEvolutionLearningRule
{
public:
	MockEvolutionLearningRule(LightBulb::AbstractEvolutionLearningRuleOptions& options_):AbstractEvolutionLearningRule(options_) {};
	MOCK_METHOD0(doIteration, bool ());
	MOCK_METHOD0(initializeStartLearningAlgoritm, void ());
	MOCK_METHOD0(initializeResumeLearningAlgoritm, void ());
	MOCK_METHOD0(initializeLearningAlgoritm, void ());
	MOCK_METHOD0(initializeTry, void ());
	MOCK_METHOD0(doCalculationAfterLearningProcess, void ());
	MOCK_METHOD0(rateLearning, void ());
	MOCK_METHOD0(hasLearningSucceeded, bool ());
	MOCK_METHOD0(getLearningResult, LightBulb::AbstractLearningResult* ());
	MOCK_METHOD1(fillDefaultResults, void (LightBulb::AbstractLearningResult&));
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD0(setHelperToUsedObjects, void ());
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(getWorld, const LightBulb::AbstractEvolutionWorld& ());
	MOCK_METHOD0(getWorld, LightBulb::AbstractEvolutionWorld& ());
};

#endif
