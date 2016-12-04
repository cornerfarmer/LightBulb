#pragma once

#ifndef _TOURNAMENTCOMBININGSTRATEGY_H_
#define _TOURNAMENTCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>
#include <memory>

// Include
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief Combines the individuals in a form similar to a tournament.
	 * \details The algorith randomly selects two individuals, compares them and puts the winning one into the next round.
	 * This continues unti there is only one individual left. The fitness values are calculated from the victory rounds.
	 */
	class TournamentCombiningStrategy : public AbstractCombiningStrategy
	{
	private:
		/**
		 * \brief True, if the individuals should be shuffled before starting a new round.
		 */
		bool doShuffleBeforeTournament;
		/**
		 * \brief The individuals from the current round.
		 */
		std::unique_ptr<std::vector<AbstractIndividual*>> currentLevel;
		/**
		* \brief The individuals which reached the next round.
		*/
		std::unique_ptr<std::vector<AbstractIndividual*>> nextLevel;
		/**
		 * \brief Processes the next round.
		 * \param environment The environment where the individuals should be compared.
		 */
		void processLevel(AbstractCoevolutionEnvironment* environment);
		// Inherited:
		void combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) override;
	public:
		/**
		 * \brief Creates the tournament combining strategy.
		 * \param doShuffleBeforeTournament_ True, if the individuals should be shuffled before starting a new round.
		 */
		TournamentCombiningStrategy(bool doShuffleBeforeTournament_ = true);
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const override;
	};
}

#endif
