#pragma once

#ifndef _ABSTRACTSELECTIONFUNCTION_H_
#define _ABSTRACTSELECTIONFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

// Library includes
#include <vector>

namespace LightBulb
{
	/**
	 * \brief Describes a random function which chooses one or multiple elements with different probabilities.
	 */
	class AbstractSelectionFunction : public AbstractRandomGeneratorUser
	{
	private:
	public:
		/**
		 * \brief Chooses one element from a pool of elements with different probabilities.
		 * \param probabilities Determines how many elements are available and which pobabilities they have.
		 * \return The number of the chosen element.
		 */
		virtual int execute(const std::vector<double> &probabilities) const = 0;
		/**
		 * \brief Chooses multiple elements from a pool of elements with different probabilities.
		 * \param probabilities Determines how many elements are available and which pobabilities they have.
		 * \param selectionCount Sets how many elements should be chosen.
		 * \return The numbers of the chosen element.
		 */
		virtual std::vector<int> execute(const std::vector<double> &probabilities, int selectionCount) const = 0;
	};
}

#endif
