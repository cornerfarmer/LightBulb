// Includes
#include "Random/ZigguratGenerator.hpp"
#include "Lib/ziggurat.hpp"

namespace LightBulb
{
	ZigguratGenerator::ZigguratGenerator(int seed)
		:AbstractRandomGenerator(seed)
	{
		ZigguratGenerator::reset();
	}

	double ZigguratGenerator::randDouble()
	{
		return r4_nor(state, kn, fn, wn);
	}

	void ZigguratGenerator::reset()
	{
		state = seed;
		r4_nor_setup(kn, fn, wn);
	}
}
