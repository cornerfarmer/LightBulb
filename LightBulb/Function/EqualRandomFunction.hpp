#pragma once

#ifndef _EQUALRANDOMFUNCTION_H_
#define _EQUALRANDOMFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/AbstractRandomFunction.hpp"

class EqualRandomFunction : public AbstractRandomFunction
{
private:
public:
	// Inherited:	
	int execute(int elementCount);
};

#endif
