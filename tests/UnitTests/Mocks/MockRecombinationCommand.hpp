#pragma once

#ifndef _MOCKRECOMBINATIONCOMMAND_H_
#define _MOCKRECOMBINATIONCOMMAND_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractRecombinationCommand.hpp>

class MockRecombinationCommand : public LightBulb::AbstractRecombinationCommand
{
public:
	MockRecombinationCommand()
		: AbstractRecombinationCommand(nullptr, nullptr)
	{
	}

	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD2(select, void (const std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&, std::map<LightBulb::AbstractIndividual*, int>&));
	MOCK_METHOD3(execute, void (std::vector<LightBulb::AbstractIndividual*>&, std::map<LightBulb::AbstractIndividual*, int>&, std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
