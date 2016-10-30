#pragma once

#ifndef _ABSTRACTMUTATIONALGORITHM_H_
#define _ABSTRACTMUTATIONALGORITHM_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library Includes
#include <memory>
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	// A algorithm which mutates the given object.
	class AbstractMutationAlgorithm : public virtual AbstractCloneable, public AbstractRandomGeneratorUser
	{
	public:
		virtual ~AbstractMutationAlgorithm() {}
		friend void swap(AbstractMutationAlgorithm& lhs, AbstractMutationAlgorithm& rhs) noexcept {	}
		// Mutates the given evolution object.
		virtual void execute(AbstractEvolutionObject& object1) = 0;
		virtual void initialize(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) {};
	};
}

#endif
