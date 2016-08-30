
#pragma once

#ifndef _STANDARDRANDOMGENERATOR_H_
#define _STANDARDRANDOMGENERATOR_H_

// Include
#include "AbstractRandomGenerator.hpp"

// Library Includes
#include <random>
#include <ctime>

// Forward declarations

template<class URNG = std::default_random_engine>
class StandardRandomGenerator : public AbstractRandomGenerator
{
protected:
	int seed;
	URNG generator;
	std::uniform_real_distribution<double> uniformDistribution;
public:

	StandardRandomGenerator()
		:generator(time(NULL))
	{
		
	}

	double randDouble()
	{
		return uniformDistribution(generator);
	}

	double randDouble(double a, double b)
	{
		return randDouble() * (b - a) + a;
	}

	int randInt(int a, int b)
	{
		std::uniform_int_distribution<int> distribution(a, b);
		return distribution(generator);
	}

	int getSeed()
	{
		return seed;
	}

	void setSeed(int newSeed)
	{
		seed = newSeed;
		generator.seed(newSeed);
	}

};

#endif
