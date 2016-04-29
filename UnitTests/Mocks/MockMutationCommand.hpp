#pragma once

#ifndef _MOCKMUTATIONCOMMAND_H_
#define _MOCKMUTATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractMutationCommand.hpp>

class MockMutationCommand : public AbstractMutationCommand
{
public:

	MockMutationCommand()
		: AbstractMutationCommand(NULL, NULL)
	{
	}
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD2(select, void (std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::map<AbstractEvolutionObject*, int>*));
};

#endif
