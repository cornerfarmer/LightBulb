#pragma once

#ifndef _ZIGGURATGENERATOR_H_
#define _ZIGGURATGENERATOR_H_

#include "Lib/ziggurat.hpp"

namespace LightBulb
{
	class ZigguratGenerator
	{
	private:
		static float fn[128];
		static uint32_t kn[128];
		static float wn[129];
		static bool initialized;
		static uint32_t seed;

		static void initialize();
	public:
		static float next();
	};
}

#endif