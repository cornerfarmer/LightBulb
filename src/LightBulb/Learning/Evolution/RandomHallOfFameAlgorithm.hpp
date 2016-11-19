#pragma once

#ifndef _RANDOMHALLOFFAMEALGORITHM_H_
#define _RANDOMHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	* \brief Describes an hall of fame algorithm where individuals are evaluated against random members of the hall of fame.
	*/
	class RandomHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
	{
	private:
		/**
		* \brief Determines the number of competitions per individual.
		*/
		int amountOfCompetitionsPerIndividual;
	protected:
		// Inherited:
		void evaluateIndividuals(std::vector<AbstractIndividual*>& individuals) override;
	public:
		/**
		 * \brief Creates a random hall of fame algorithm.
		 * \param amountOfCompetitionsPerIndividual_ Determines the number of competitions per individual.
		 */
		RandomHallOfFameAlgorithm(int amountOfCompetitionsPerIndividual_ = 0);
	};
}

USE_EXISTING_PARENT_SINGLE_SERIALIZATION(LightBulb::RandomHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb::AbstractHallOfFameAlgorithm, LightBulb)

#endif
