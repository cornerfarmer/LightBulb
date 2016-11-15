#pragma once

#ifndef _TOURNAMENTCOMBININGSTRATEGY_H_
#define _TOURNAMENTCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>
#include <memory>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief Combines the evolution objects in a form similar to a tournament.
	 * \details The algorith randomly selects two objects, compares them and puts the winning one into the next round.
	 * This continues unti there is only one object left. The fitness values are calculated from the victory rounds.
	 */
	class TournamentCombiningStrategy : public AbstractCombiningStrategy
	{
	private:
		/**
		 * \brief True, if the objects should be shuffled before starting a new round.
		 */
		bool doShuffleBeforeTournament;
		/**
		 * \brief The objects from the current round.
		 */
		std::unique_ptr<std::vector<AbstractEvolutionObject*>> currentLevel;
		/**
		* \brief The objects which reached the next round.
		*/
		std::unique_ptr<std::vector<AbstractEvolutionObject*>> nextLevel;
		/**
		 * \brief Processes the next round.
		 * \param world The world where the objects should be compared.
		 */
		void processLevel(AbstractCoevolutionWorld* world);
		// Inherited:
		void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractEvolutionObject*>& firstObjects, std::vector<AbstractEvolutionObject*>& secondObjects) override;
	public:
		/**
		 * \brief Creates the tournament combining strategy.
		 * \param doShuffleBeforeTournament_ True, if the objects should be shuffled before starting a new round.
		 */
		TournamentCombiningStrategy(bool doShuffleBeforeTournament_ = true);
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const override;
	};
}

#endif
