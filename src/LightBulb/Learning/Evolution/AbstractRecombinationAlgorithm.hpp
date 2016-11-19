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
	class AbstractIndividual;
	/**
	 * \brief A algorithm that recombines two individuals to a new one.
	 */
	class AbstractRecombinationAlgorithm : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
	{
	private:
	public:
		virtual ~AbstractRecombinationAlgorithm() {}
		/**
		 * \brief This method combines the two given individuals to a new one which will be stored inside the first given individual.
		 * \param individual1 The first individual which will contain the result of the recombination.
		 * \param individual2 The second individual.
		 */
		virtual void execute(AbstractIndividual& individual1, AbstractIndividual& individual2) = 0;
	};
}

#endif
