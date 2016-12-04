#pragma once

#ifndef _ROUNDROBINCOMBININGSTRATEGY_H_
#define _ROUNDROBINCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief A combining strategy which combines every individual with every individual.
	 */
	class RoundRobinCombiningStrategy : public AbstractCombiningStrategy
	{
	private:
		// Inherited:
		void combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) override;
	public:
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const override;
	};
}

#endif
