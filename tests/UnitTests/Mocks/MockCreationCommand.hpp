#pragma once

#ifndef _MOCKCREATIONCOMMAND_H_
#define _MOCKCREATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractCreationCommand.hpp>
#include <LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp>

class MockCreationCommand : public LightBulb::AbstractCreationCommand
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD2(execute, void (LightBulb::AbstractEvolutionEnvironment&, std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
