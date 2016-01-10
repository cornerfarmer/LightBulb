#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULE_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"

// Library Includes

// Forward declarations

class BipartiteEvolutionLearningRule
{
protected:
	EvolutionLearningRule* learningRule1;
	EvolutionLearningRule* learningRule2;
public:
	BipartiteEvolutionLearningRule(EvolutionLearningRule* learningRule1_, EvolutionLearningRule* learningRule2_);
	// Executes the learning process
	LearningResult doLearning();
};

#endif
