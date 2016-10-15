#pragma once

#ifndef _EQUALRANDOMFUNCTION_H_
#define _EQUALRANDOMFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a uniform distribution.
	 * \details Every number has the same probability.
	 */
	class EqualRandomFunction : public AbstractRandomFunction
	{
	private:
	public:
		// Inherited:	
		int execute(int elementCount) const override;
	};
}

#endif
