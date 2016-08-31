#pragma once

#ifndef _MOCKSELECTIONCOMMAND_H_
#define _MOCKSELECTIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractSelectionCommand.hpp>

class MockSelectionCommand : public AbstractSelectionCommand
{
public:
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD3(execute, void (std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::vector<AbstractEvolutionObject*>*, std::vector<AbstractEvolutionObject*>*));
	MOCK_METHOD1(setRandomGenerator, void (AbstractRandomGenerator*));
};

#endif
