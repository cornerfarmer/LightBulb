// Includes
#include "Function/ZigguratGenerator.hpp"

#include "Lib/ziggurat.hpp"

float ZigguratGenerator::fn[128];
uint32_t ZigguratGenerator::kn[128];
float ZigguratGenerator::wn[129];
bool ZigguratGenerator::initialized = false;
uint32_t ZigguratGenerator::seed = 123456789;

void ZigguratGenerator::initialize()
{
	r4_nor_setup(kn, fn, wn);
	initialized = true;
}

float ZigguratGenerator::next()
{
	if (!initialized)
		initialize();

	float value;

	value = r4_nor(seed, kn, fn, wn);

	return value;
}