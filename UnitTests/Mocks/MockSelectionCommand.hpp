#pragma once

#ifndef _MOCKSELECTIONCOMMAND_H_
#define _MOCKSELECTIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractSelectionCommand.hpp>

class MockSelectionCommand : public LightBulb::AbstractSelectionCommand
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger*));
	MOCK_METHOD3(execute, void (std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>*, std::vector<LightBulb::AbstractEvolutionObject*>*, std::vector<LightBulb::AbstractEvolutionObject*>*));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator*));
};

#endif
