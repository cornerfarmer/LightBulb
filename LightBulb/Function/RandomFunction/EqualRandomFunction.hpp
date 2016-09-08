#pragma once

#ifndef _EQUALRANDOMFUNCTION_H_
#define _EQUALRANDOMFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

/**
 * \brief Describes a uniform distribution.
 * \details Every number has the same probability.
 */
class EqualRandomFunction : public AbstractRandomFunction
{
private:
public:
	// Inherited:	
	int execute(int elementCount) override;
};

#endif
