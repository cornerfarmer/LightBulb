#pragma once

#ifndef _ABSTRACTRANDOMFUNCTION_H_
#define _ABSTRACTRANDOMFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	/**
	 * \brief Stellt eine Function da die aus einer gegebenen Anzahl an Elementen eines zufällig auswählt.
	 */
	class AbstractRandomFunction : public AbstractRandomGeneratorUser
	{
	private:
	public:
		virtual ~AbstractRandomFunction() {}
		/**
		 * \brief Wählt eine zufällige Zahl zwischen 0 und elementCount - 1.
		 * \param elementCount Die Anzahl der wählbaren Elemente
		 * \return Das gewählte Element
		 */
		virtual int execute(int elementCount) = 0;
	};
}

#endif
