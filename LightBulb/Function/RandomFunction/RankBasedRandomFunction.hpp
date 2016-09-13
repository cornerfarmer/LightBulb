#pragma once

#ifndef _RANKBASEDRANDOMFUNCTION_H_
#define _RANKBASEDRANDOMFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a random function where lower (= higher ranked) numbers have higher probabilities.
	 * \details Probability distribution: \n \n \f$f(r) = 1 + (s - 1) * e^{-(s-1)*\frac{r}{n}}\f$ \n \n
	 *	\f$r \in [1;n]\f$
	 */
	class RankBasedRandomFunction : public AbstractRandomFunction
	{
	private:
		/**
		 * \brief Determines how many times the number with the highest rank is more probable than the one with the lowest rank.
		 */
		double selectivePressure;
	public:
		/**
		 * \brief Creates a RankBasedRandomFunction
		 * \param selectivePressure_ Determines how many times the number with the highest rank is more probable than the one with the lowest rank.
		 */
		RankBasedRandomFunction(double selectivePressure_ = 8);
		// Inherited:	
		int execute(int elementCount) override;
	};
}

#endif
