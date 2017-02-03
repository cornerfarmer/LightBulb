#pragma once

#ifndef _MOCKEVOLUTIONLEARNINGRULE_H_
#define _MOCKEVOLUTIONLEARNINGRULE_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp>
#include <LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp>
#include <LightBulb/Learning/AbstractLearningResult.hpp>
#include <LightBulb/Logging/AbstractLogger.hpp>

class MockEvolutionLearningRule : public LightBulb::AbstractEvolutionLearningRule
{
public:
	MockEvolutionLearningRule(LightBulb::AbstractEvolutionLearningRuleOptions& options_):AbstractEvolutionLearningRule(options_) {};
	MOCK_METHOD0(doIteration, void());
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
	MOCK_CONST_METHOD0(getEnvironment, const LightBulb::AbstractEvolutionEnvironment& ());
	MOCK_METHOD0(getEnvironment, LightBulb::AbstractEvolutionEnvironment& ());
	MOCK_METHOD0(shouldSkipTry, bool ());
};

#endif
