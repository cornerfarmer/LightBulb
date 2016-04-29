#pragma once

#ifndef _MOCKRECOMBINATIONCOMMAND_H_
#define _MOCKRECOMBINATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractRecombinationCommand.hpp>

class MockRecombinationCommand : public AbstractRecombinationCommand
{
public:
	MockRecombinationCommand()
		: AbstractRecombinationCommand(NULL, NULL)
	{
	}

	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD2(select, void (std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::map<AbstractEvolutionObject*, int>*));
};

#endif
