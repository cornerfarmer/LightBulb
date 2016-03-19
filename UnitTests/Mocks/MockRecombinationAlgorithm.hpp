#pragma once

#ifndef _MOCKRECOMBINATIONALGORITHM_H_
#define _MOCKRECOMBINATIONALGORITHM_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractRecombinationAlgorithm.hpp>

class MockRecombinationAlgorithm : public AbstractRecombinationAlgorithm
{
public:
	MOCK_METHOD2(execute, void (AbstractEvolutionObject*, AbstractEvolutionObject*));
};

#endif
