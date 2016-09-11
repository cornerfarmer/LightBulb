#pragma once

#ifndef _MOCKREUSECOMMAND_H_
#define _MOCKREUSECOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractReuseCommand.hpp>

class MockReuseCommand : public LightBulb::AbstractReuseCommand
{
public:
	MockReuseCommand()
		: LightBulb::AbstractReuseCommand(NULL)
	{
	}

	MOCK_METHOD3(execute, void (std::vector<LightBulb::AbstractEvolutionObject*>*, std::map<LightBulb::AbstractEvolutionObject*, int>*, std::vector<LightBulb::AbstractEvolutionObject*>*));
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger*));
	MOCK_METHOD2(select, void (std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>*, std::map<LightBulb::AbstractEvolutionObject*, int>*));
};

#endif
