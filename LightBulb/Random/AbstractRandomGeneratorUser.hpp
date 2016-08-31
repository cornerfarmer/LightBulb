
#pragma once

#ifndef _ABSTRACTRANDOMGENERATORUSER_H_
#define _ABSTRACTRANDOMGENERATORUSER_H_

// Include
#include "AbstractRandomGenerator.hpp"

// Library Includes

// Forward declarations

class AbstractRandomGeneratorUser
{
protected:
	AbstractRandomGenerator* randomGenerator;
public:
	virtual void setRandomGenerator(AbstractRandomGenerator* randomGenerator_);
	AbstractRandomGenerator* getRandomGenerator();
};

#endif
