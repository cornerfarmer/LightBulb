#pragma once

#ifndef _BESTREUSESELECTOR_H_
#define _BESTREUSESELECTOR_H_

// Library includes
#include <vector>
#include <utility>

// Includes
#include "AbstractReuseSelector.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	/**
	 * \brief Selects the N best objects for reusing.
	 */
	class BestReuseSelector : public AbstractReuseSelector
	{
	private:
	protected:
		// Inherited:
		void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	public:
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

#endif
