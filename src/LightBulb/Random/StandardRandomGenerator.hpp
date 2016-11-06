
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
		 * \brief The current random engine.
		 */
		URNG generator;
		/**
		 * \brief The default uniform distribution which is used for numbers between 0 and 1.
		 */
		std::uniform_real_distribution<double> uniformDistribution;
		// Inherited:
		void reset() override
		{
			generator.seed(seed);
		}
	public:
		/**
		 * \brief Creates a new StandardRandomGenerator.
		 * \param seed_ The seed which should be used for initializing. (-1 means random)
		 */
		StandardRandomGenerator(int seed_ = -1)
			:AbstractRandomGenerator(seed_), generator(seed_)
		{
			StandardRandomGenerator<URNG>::reset();
		}

		// Inherited:
		double randDouble() override
		{
			return uniformDistribution(generator);
		}

		int randInt(int a, int b) override
		{
			std::uniform_int_distribution<int> distribution(a, b);
			return distribution(generator);
		}
	};
}

#include "IO/StandardRandomGeneratorIO.hpp"

#endif
