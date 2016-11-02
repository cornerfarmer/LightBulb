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
	/**
	 * \brief Describes an algorithm which mutates objects.
	 */
	class AbstractMutationAlgorithm : public virtual AbstractCloneable, public AbstractRandomGeneratorUser
	{
	public:
		virtual ~AbstractMutationAlgorithm() {}
		friend void swap(AbstractMutationAlgorithm& lhs, AbstractMutationAlgorithm& rhs) noexcept {	}
		/**
		 * \brief Mutates the given object.
		 * \param object1 The object to mutate.
		 */
		virtual void execute(AbstractEvolutionObject& object1) = 0;
		/**
		 * \brief Initializes the algorithm.
		 * \param highscore The current highscore.
		 */
		virtual void initialize(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) {};
	};
}

#endif
