// Includes
#include "LightBulb/Random/XorShfGenerator.hpp"

namespace LightBulb
{
	XorShfGenerator::XorShfGenerator(int seed): AbstractRandomGenerator(seed)
	{
		XorShfGenerator::reset();
	}

	XorShfGenerator::result_type XorShfGenerator::min() const
	{
		return (0);
	}

	XorShfGenerator::result_type XorShfGenerator::max() const
	{ // return maximum possible generated value
		return static_cast<result_type>(-1);
	}

	XorShfGenerator::result_type XorShfGenerator::operator()()
	{
		unsigned long t;
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

		t = x;
		x = y;
		y = z;
		z = t ^ x ^ y;

		return z;
	}

	float XorShfGenerator::randFloat()
	{
		return static_cast<float>((*this)() - min()) / max();
	}

	void XorShfGenerator::reset()
	{
		x = 123456789;
		y = seed;
		z = 521288629;
	}
}
