#pragma once

#ifndef _MOCKREUSECOMMAND_H_
#define _MOCKREUSECOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractReuseCommand.hpp>

class MockReuseCommand : public AbstractReuseCommand
{
public:
	MockReuseCommand()
		: AbstractReuseCommand(NULL)
	{
	}

	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD2(select, void (std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::map<AbstractEvolutionObject*, int>*));
};

#endif
