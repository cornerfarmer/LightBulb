#pragma once

#ifndef _ABSTRACTRECOMBINATIONALGORITHM_H_
#define _ABSTRACTRECOMBINATIONALGORITHM_H_

// Library Includes

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"
#include "Tools/AbstractCloneable.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	/**
	 * \brief A algorithm that recombines two evolution objects to a new one.
	 */
	class AbstractRecombinationAlgorithm : public virtual AbstractCloneable, public AbstractRandomGeneratorUser
	{
	private:
	public:
		virtual ~AbstractRecombinationAlgorithm() {}
		/**
		 * \brief This method combines the two given objects to a new one which will be stored inside the first given object.
		 * \param object1 The first object which will contain the result of the recombination.
		 * \param object2 The second object.
		 */
		virtual void execute(AbstractEvolutionObject& object1, AbstractEvolutionObject& object2) = 0;
	};
}

#endif
