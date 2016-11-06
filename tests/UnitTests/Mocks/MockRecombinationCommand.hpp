#pragma once

#ifndef _MOCKRECOMBINATIONCOMMAND_H_
#define _MOCKRECOMBINATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractRecombinationCommand.hpp>

class MockRecombinationCommand : public LightBulb::AbstractRecombinationCommand
{
public:
	MockRecombinationCommand()
		: AbstractRecombinationCommand(nullptr, nullptr)
	{
	}

	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD2(select, void (const std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>&, std::map<LightBulb::AbstractEvolutionObject*, int>&));
	MOCK_METHOD3(execute, void (std::vector<LightBulb::AbstractEvolutionObject*>&, std::map<LightBulb::AbstractEvolutionObject*, int>&, std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
