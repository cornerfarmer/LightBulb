#pragma once

#ifndef _MOCKMUTATIONALGORITHM_H_
#define _MOCKMUTATIONALGORITHM_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractMutationAlgorithm.hpp>

class MockMutationAlgorithm : public AbstractMutationAlgorithm
{
public:
	MOCK_METHOD1(execute, void (AbstractEvolutionObject*));
};

#endif
