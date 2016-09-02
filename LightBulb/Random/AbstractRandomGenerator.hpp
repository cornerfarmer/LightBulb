
#pragma once

#ifndef _ABSTRACTRANDOMGENERATOR_H_
#define _ABSTRACTRANDOMGENERATOR_H_

// Include

// Library Includes
#include "IO/UseParentSerialization.hpp"

// Forward declarations

class AbstractRandomGenerator
{
protected:
public:
	virtual double randDouble() = 0;
	virtual double randDouble(double a, double b) = 0;
	virtual int randInt(int a, int b) = 0;
	virtual int getSeed() = 0;
	virtual void setSeed(int newSeed) = 0;
};

EMPTY_SERIALIZATION(AbstractRandomGenerator)

#endif
