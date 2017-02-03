#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHM_H_
#define _ABSTRACTHALLOFFAMEALGORITHM_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "LightBulb/Logging/AbstractLoggable.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionEnvironment;
	class AbstractIndividual;
	/**
	 * \brief Describes the results of a AbstractCombiningStrategy.
	 * \details Maps: First individual - Second individual - round number => True, if first individual has won.
	 */
	typedef std::map<AbstractIndividual*, std::map<AbstractIndividual*, std::map<int, bool>>> CombiningStrategyResults;
	/**
	 * \brief Describes an algorithm which stores some good individuals of the time to make sure their knowledge will not be lost.
	 */
	class AbstractHallOfFameAlgorithm : public AbstractLoggable
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm);
	private:
		/**
		 * \brief Stores the current CombiningStrategyResults.
		 */
		CombiningStrategyResults* currentResults;
	protected:
		/**
		 * \brief The current environment to use for simulations.
		 */
		AbstractCoevolutionEnvironment* currentEnvironment;
		/**
		 * \brief All members of the hall of fame.
		 */
		std::vector<std::unique_ptr<AbstractIndividual>> members;
		/**
		 * \brief Compares the given individual with one memeber of the hall of fame.
		 * \param individual The individual to evaluate.
		 * \param memberID The id of the member to use.
		 * \param round The round number.
		 */
		void simulateAgainstMember(AbstractIndividual& individual, int memberID, int round);
		/**
		 * \brief Evaluates the given individuals.
		 * \param individuals A vector of individuals.
		 */
		virtual void evaluateIndividuals(std::vector<AbstractIndividual*>& individuals) = 0;
	public:
		AbstractHallOfFameAlgorithm();
		~AbstractHallOfFameAlgorithm();
		/**
		 * \brief Compares individuals from the given environment with members of the hall of fame.
		 * \param environment The environment to use.
		 * \param prevResults The CombiningStrategyResults where the new results should be stored in.
		 */
		virtual void execute(AbstractCoevolutionEnvironment& environment, CombiningStrategyResults& prevResults);
		/**
		 * \brief Adds the given individual to the hall of fame.
		 * \param newMember The new member to add.
		 */
		virtual void addMember(AbstractIndividual* newMember);
	};
}

#include "LightBulb/IO/AbstractHallOfFameAlgorithmIO.hpp"

#endif
