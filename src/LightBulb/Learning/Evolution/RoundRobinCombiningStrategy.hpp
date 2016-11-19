#pragma once

#ifndef _ROUNDROBINCOMBININGSTRATEGY_H_
#define _ROUNDROBINCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief A combining strategy which combines every individual with every individual.
	 */
	class RoundRobinCombiningStrategy : public AbstractCombiningStrategy
	{
	private:
		// Inherited:
		void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) override;
	public:
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const override;
	};
}

#endif
