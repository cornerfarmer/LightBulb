#pragma once

#ifndef _FULLHALLOFFAMEALGORITHM_H_
#define _FULLHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "LightBulb/Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes an hall of fame algorithm where individuals are evaluated against ALL members of the hall of fame.
	 */
	class FullHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
	{
	private:
	protected:
		// Inherited:
		void evaluateIndividuals(std::vector<AbstractIndividual*>& individual) override;
	};
}

USE_EXISTING_PARENT_SINGLE_SERIALIZATION(LightBulb::FullHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb)

#endif
