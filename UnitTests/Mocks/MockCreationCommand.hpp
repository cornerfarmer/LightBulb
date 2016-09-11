#pragma once

#ifndef _MOCKCREATIONCOMMAND_H_
#define _MOCKCREATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCreationCommand.hpp>
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

class MockCreationCommand : public LightBulb::AbstractCreationCommand
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator*));
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger*));
	MOCK_METHOD2(execute, void (LightBulb::AbstractEvolutionWorld&, std::vector<LightBulb::AbstractEvolutionObject*>*));
};

#endif
