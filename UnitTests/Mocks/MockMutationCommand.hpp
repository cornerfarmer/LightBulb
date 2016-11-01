#pragma once

#ifndef _MOCKMUTATIONCOMMAND_H_
#define _MOCKMUTATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractMutationCommand.hpp>

class MockMutationCommand : public LightBulb::AbstractMutationCommand
{
public:

	MockMutationCommand()
		: AbstractMutationCommand(nullptr, nullptr)
	{
	}
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD2(select, void (const std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>&, std::map<LightBulb::AbstractEvolutionObject*, int>&));
	MOCK_METHOD3(execute, void (std::vector<LightBulb::AbstractEvolutionObject*>&, std::map<LightBulb::AbstractEvolutionObject*, int>&, std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
