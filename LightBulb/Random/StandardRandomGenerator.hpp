
#pragma once

#ifndef _STANDARDRANDOMGENERATOR_H_
#define _STANDARDRANDOMGENERATOR_H_

// Include
#include "AbstractRandomGenerator.hpp"

// Library Includes
#include <random>
#include <chrono>

namespace LightBulb
{
	/**
	 * \brief Describes a random generator which uses the built-in c++ random engines.
	 * \tparam URNG The random engine which should be used.
	 */
	template<class URNG = std::default_random_engine>
	class StandardRandomGenerator : public AbstractRandomGenerator
	{
		template <class Archive, class T>
		friend void load(Archive& archive, StandardRandomGenerator<T>& standardRandomGenerator);
		template <class Archive, class T>
		friend void save(Archive& archive, StandardRandomGenerator<T> const& standardRandomGenerator);
	protected:
		/**
		 * \brief The current seed.
		 */
		int seed;
		/**
		 * \brief The current random engine.
		 */
		URNG generator;
		/**
		 * \brief The default uniform distribution which is used for numbers between 0 and 1.
		 */
		std::uniform_real_distribution<double> uniformDistribution;
	public:
		/**
		 * \brief Creates a new StandardRandomGenerator.
		 * \param seed_ The seed which should be used for initializing. (-1 means random)
		 */
		StandardRandomGenerator(int seed_ = -1)
			:generator(seed_)
		{
			seed = seed_;
			if (seed == -1)
				setSeed(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		}

		// Inherited:
		double randDouble() override
		{
			return uniformDistribution(generator);
		}

		double randDouble(double a, double b) override
		{
			return randDouble() * (b - a) + a;
		}

		int randInt(int a, int b) override
		{
			std::uniform_int_distribution<int> distribution(a, b);
			return distribution(generator);
		}

		int getSeed() override
		{
			return seed;
		}

		void setSeed(int newSeed) override
		{
			seed = newSeed;
			generator.seed(newSeed);
		}
	};
}

#include "IO/StandardRandomGeneratorIO.hpp"

#endif
