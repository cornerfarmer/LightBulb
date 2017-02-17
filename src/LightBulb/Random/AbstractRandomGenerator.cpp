// Includes
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include <chrono>

LightBulb::AbstractRandomGenerator::AbstractRandomGenerator(int seed_)
{
	if (seed_ == -1)
		seed = getRandomSeed();
	else
		seed = seed_;
}

int LightBulb::AbstractRandomGenerator::getRandomSeed()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

const LightBulb::Vector<>& LightBulb::AbstractRandomGenerator::randMultipleDouble(int count)
{
	if (count > randomNumberCache.getEigenValue().size())
		randomNumberCache.getEigenValueForEditing().resize(count);

	for (int i = 0; i < count; i++)
	{
		randomNumberCache.getEigenValueForEditing()[i] = randFloat();
	}

	return randomNumberCache;
}

float LightBulb::AbstractRandomGenerator::randFloat(float a, float b)
{
	return randFloat() * (b - a) + a;
}

int LightBulb::AbstractRandomGenerator::randInt(int a, int b)
{
	return randFloat() * (b - a + 1) + a;
}


int LightBulb::AbstractRandomGenerator::getSeed() const
{
	return seed;
}

void LightBulb::AbstractRandomGenerator::setSeed(int newSeed)
{
	if (newSeed == -1)
		seed = getRandomSeed();
	else
		seed = newSeed;
	reset();
}
