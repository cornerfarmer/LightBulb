#pragma once

#ifndef _FULLHALLOFFAMEALGORITHM_H_
#define _FULLHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes an hall of fame algorithm where objects are evaluated against ALL members of the hall of fame.
	 */
	class FullHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
	{
	private:
	protected:
		// Inherited:
		void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) override;
	};
}

USE_EXISTING_PARENT_SINGLE_SERIALIZATION(LightBulb::FullHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb)

#endif
