#pragma once

#ifndef _XORSHFGENERATOR_H_
#define _XORSHFGENERATOR_H_

// Includes
#include "LightBulb/Random/AbstractRandomGenerator.hpp"

namespace LightBulb
{
	class XorShfGenerator : public AbstractRandomGenerator
	{
	private:
	public:
		typedef unsigned long result_type;

		unsigned long x;
		unsigned long y;
		unsigned long z;

		explicit XorShfGenerator(int seed = -1);

		result_type min() const;

		result_type max() const;

		result_type operator()();

		double randDouble() override;

		void reset() override;
	};
}

#endif