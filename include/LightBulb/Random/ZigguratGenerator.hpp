#pragma once

#ifndef _ZIGGURATGENERATOR_H_
#define _ZIGGURATGENERATOR_H_

// Includes
#include "LightBulb/Lib/ziggurat.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"

namespace LightBulb
{
	class ZigguratGenerator : public AbstractRandomGenerator
	{
		template <class Archive>
		friend void load(Archive& archive, ZigguratGenerator& zigguratGenerator);
		template <class Archive>
		friend void save(Archive& archive, ZigguratGenerator const& zigguratGenerator);
	private:
		float fn[128];
		uint32_t kn[128];
		float wn[129];
		uint32_t state;
	protected:
		void reset() override;
	public:
		ZigguratGenerator(int seed = -1);
		double randDouble() override;
	};
}

#include "LightBulb/IO/ZigguratGeneratorIO.hpp"

#endif