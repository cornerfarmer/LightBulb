
#pragma once

#ifndef _ABSTRACTRANDOMGENERATORUSER_H_
#define _ABSTRACTRANDOMGENERATORUSER_H_

// Include
#include "LightBulb/Random/AbstractRandomGenerator.hpp"

// Library Includes

namespace LightBulb
{
	/**
	 * \brief Can be used by every class which needs to generate random numbers.
	 */
	class AbstractRandomGeneratorUser
	{
	protected:
		/**
		 * \brief The random generator which is used.
		 * \note Before the random generator can be used, setRandomGenerator() should be called.
		 */
		AbstractRandomGenerator* randomGenerator;
	public:
		virtual ~AbstractRandomGeneratorUser() {};
		/**
		 * \brief Creates an AbstractRandomGeneratorUser
		 */
		AbstractRandomGeneratorUser();
		/**
		 * \brief Sets the random generator which should be used.
		 * \param randomGenerator_ The random generator.
		 */
		virtual void setRandomGenerator(AbstractRandomGenerator& randomGenerator_);
		/**
		 * \brief Returns the currently used random generator.
		 * \return The random generator.
		 */
		AbstractRandomGenerator& getRandomGenerator();
	};
}

#endif
