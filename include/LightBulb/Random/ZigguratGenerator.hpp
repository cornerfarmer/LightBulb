#pragma once

#ifndef _ZIGGURATGENERATOR_H_
#define _ZIGGURATGENERATOR_H_

// Includes
#include "LightBulb/Lib/ziggurat.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

namespace LightBulb
{
	class ZigguratGenerator : public AbstractRandomGenerator
	{
		template <class Archive>
		friend void load(Archive& archive, ZigguratGenerator& zigguratGenerator);
		template <class Archive>
		friend void save(Archive& archive, ZigguratGenerator const& zigguratGenerator);
	private:
		Vector<> fn;
		Vector<cl_uint> kn;
		Vector<> wn;
		Scalar<cl_uint> state;
	protected:
		void reset() override;
	public:
		ZigguratGenerator(int seed = -1);
		double randDouble() override;
		const Vector<>& randMultipleDouble(int count) override;
	};
}

#include "LightBulb/IO/ZigguratGeneratorIO.hpp"

#endif