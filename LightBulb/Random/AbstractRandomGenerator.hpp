
#pragma once

#ifndef _ABSTRACTRANDOMGENERATOR_H_
#define _ABSTRACTRANDOMGENERATOR_H_

// Include

// Library Includes
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a generator of random numbers.
	 */
	class AbstractRandomGenerator
	{
	protected:
	public:
		/**
		 * \brief Generates a random double between [0, 1[.
		 * \return The random number.
		 */
		virtual double randDouble() = 0;
		/**
		 * \brief Generates a random double between [a, b[.
		 * \param a The lower boundary.
		 * \param b The upper boundary.
		 * \return The random number.
		 */
		virtual double randDouble(double a, double b) = 0;
		/**
		* \brief Generates a random int between [a, b].
		* \param a The lower boundary.
		* \param b The upper boundary.
		* \return The random number.
		*/
		virtual int randInt(int a, int b) = 0;
		/**
		 * \brief Returns the current seed of the random generator.
		 * \return The seed.
		 */
		virtual int getSeed() = 0;
		/**
		 * \brief Sets a new seed.
		 * \param newSeed The new seed.
		 */
		virtual void setSeed(int newSeed) = 0;
	};

}

EMPTY_SERIALIZATION(LightBulb::AbstractRandomGenerator, LightBulb)


#endif
