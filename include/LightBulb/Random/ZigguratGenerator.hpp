#pragma once

#ifndef _ZIGGURATGENERATOR_H_
#define _ZIGGURATGENERATOR_H_

// Includes
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

namespace LightBulb
{
	class Kernel;

	class ZigguratGenerator : public AbstractRandomGenerator
	{
		template <class Archive>
		friend void load(Archive& archive, ZigguratGenerator& zigguratGenerator);
		template <class Archive>
		friend void save(Archive& archive, ZigguratGenerator const& zigguratGenerator);
	private:
		std::unique_ptr<Kernel> r4NorKernel;
		std::unique_ptr<Kernel> r4NorSetupKernel;
		Vector<> fn;
		Vector<cl_uint> kn;
		Vector<> wn;
		Scalar<cl_uint> state;
	protected:
		void reset() override;
	public:
		ZigguratGenerator(int seed = -1);
		~ZigguratGenerator();
		float randFloat() override;
		const Vector<>& randMultipleDouble(int count) override;
	};
}

#include "LightBulb/IO/ZigguratGeneratorIO.hpp"

#endif