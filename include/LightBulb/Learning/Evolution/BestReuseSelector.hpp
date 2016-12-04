#pragma once

#ifndef _BESTREUSESELECTOR_H_
#define _BESTREUSESELECTOR_H_

// Library includes
#include <vector>
#include <utility>

// Includes
#include "LightBulb/Learning/Evolution/AbstractReuseSelector.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	 * \brief Selects the N best individuals for reusing.
	 */
	class BestReuseSelector : public AbstractReuseSelector
	{
	private:
	protected:
		// Inherited:
		void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
	public:
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

#endif
