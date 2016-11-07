#pragma once

#ifndef _ABSTRACTRANDOMFUNCTION_H_
#define _ABSTRACTRANDOMFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"
#include "Tools/AbstractCloneable.hpp"

namespace LightBulb
{
	/**
	 * \brief A function which chooses one of n elements randomly.
	 */
	class AbstractRandomFunction : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
	{
	private:
	public:
		virtual ~AbstractRandomFunction() {}
		/**
		 * \brief Chooses a random number between 0 and elementCount - 1.
		 * \param elementCount The number of possible elements
		 * \return The chosen element number
		 */
		virtual int execute(int elementCount) const = 0;
	};
}

#endif
