#pragma once

#ifndef _MOCKCREATIONCOMMAND_H_
#define _MOCKCREATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCreationCommand.hpp>
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

class MockCreationCommand : public AbstractCreationCommand
{
public:
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD1(execute, void (AbstractEvolutionWorld&));
};

#endif
