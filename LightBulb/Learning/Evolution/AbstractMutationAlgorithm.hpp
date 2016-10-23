#pragma once

#ifndef _ABSTRACTMUTATIONALGORITHM_H_
#define _ABSTRACTMUTATIONALGORITHM_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

// Library Includes
#include <memory>
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	// A algorithm which mutates the given object.
	class AbstractMutationAlgorithm : public AbstractRandomGeneratorUser
	{
	public:
		virtual ~AbstractMutationAlgorithm() {};
		// Mutates the given evolution object.
		virtual void execute(AbstractEvolutionObject& object1) = 0;
		virtual void initialize(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) {};
	};
}

#endif
