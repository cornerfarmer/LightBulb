#pragma once

#ifndef _ABSTRACTRANDOMFUNCTION_H_
#define _ABSTRACTRANDOMFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	/**
	 * \brief Stellt eine Function da die aus einer gegebenen Anzahl an Elementen eines zuf�llig ausw�hlt.
	 */
	class AbstractRandomFunction : public AbstractRandomGeneratorUser
	{
	private:
	public:
		virtual ~AbstractRandomFunction() {}
		/**
		 * \brief W�hlt eine zuf�llige Zahl zwischen 0 und elementCount - 1.
		 * \param elementCount Die Anzahl der w�hlbaren Elemente
		 * \return Das gew�hlte Element
		 */
		virtual int execute(int elementCount) = 0;
	};
}

#endif
