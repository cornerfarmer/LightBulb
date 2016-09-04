#pragma once

#ifndef _RANKBASEDRANDOMFUNCTION_H_
#define _RANKBASEDRANDOMFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

class RankBasedRandomFunction : public AbstractRandomFunction
{
private:
public:
	// Inherited:	
	int execute(int elementCount) override;
};

#endif
