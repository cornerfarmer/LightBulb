// Includes
#include "Random/AbstractRandomGenerator.hpp"
#include <chrono>

LightBulb::AbstractRandomGenerator::AbstractRandomGenerator(int seed_)
{
	if (seed_ == 1)
		seed = getRandomSeed();
	else
		seed = seed_;
}

int LightBulb::AbstractRandomGenerator::getRandomSeed()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

double LightBulb::AbstractRandomGenerator::randDouble(double a, double b)
{
	return randDouble() * (b - a) + a;
}

int LightBulb::AbstractRandomGenerator::randInt(int a, int b)
{
	return randDouble() * (b - a + 1) + a;
}


int LightBulb::AbstractRandomGenerator::getSeed() const
{
	return seed;
}

void LightBulb::AbstractRandomGenerator::setSeed(int newSeed)
{
	seed = newSeed;
	reset();
}
