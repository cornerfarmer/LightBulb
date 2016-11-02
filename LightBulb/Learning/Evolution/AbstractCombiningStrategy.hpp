#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Include
#include "Random/AbstractRandomGeneratorUser.hpp"

// Library Includes
#include <vector>
#include <memory>
#include <map>

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionWorld;
	class AbstractEvolutionObject;
	/**
	 * \brief Describes the results of a AbstractCombiningStrategy.
	 * \details Maps: First object - Second object - round number => True, if first object has won.
	 */
	typedef std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, std::map<int, bool>>> CombiningStrategyResults;
	/**
	 * \brief Describes a strategy for combining evolution object from one or two coevolution worlds.
	 * \details The strategy compares each two evolution objects and stores the results in a CombiningStrategyResults object.
	 */
	class AbstractCombiningStrategy : public AbstractRandomGeneratorUser
	{
	private:
		/**
		 * \brief Stores the current combining results.
		 */
		std::unique_ptr<CombiningStrategyResults> results;
		/**
		 * \brief Counts how often the first player has won.
		 */
		int firstPlayerWins;
	protected:
		/**
		 * \brief Contains a second world, if one is used.
		 */
		AbstractCoevolutionWorld* secondWorld;
		/**
		 * \brief Does the combining.
		 * \param simulationWorld The world which should be used for comparing evolution objects.
		 * \param firstObjects The first pool of evolution objects.
		 * \param secondObjects The second pool of evolution objects.
		 * \note If only one world is used, the first and second pool will be the same.
		 */
		virtual void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractEvolutionObject*>& firstObjects, std::vector<AbstractEvolutionObject*>& secondObjects) = 0;
		/**
		 * \brief Registers the result of one combination.
		 * \param firstPlayer The first player which has been used.
		 * \param secondPlayer The second player which has been used.
		 * \param round The round number.
		 * \param firstPlayerHasWon True, if the first player has won.
		 */
		void setResult(AbstractEvolutionObject& firstPlayer, AbstractEvolutionObject& secondPlayer, int round, bool firstPlayerHasWon);
	public:
		/**
		 * \brief Creates the combining strategy.
		 * \param secondWorld_ Optional a second world whose objects should be used beside the objects from the default world.
		 */
		AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_ = nullptr);
		/**
		 * \brief Executes combining of objects from the given world.
		 * \param world The world whose objects should be used.
		 * \return The combining results.
		 */
		virtual CombiningStrategyResults& execute(AbstractCoevolutionWorld& world);
		/**
		 * \brief Sets a second world whose objects should be used beside the objects from the default world.
		 * \param newSecondWorld The world to use.
		 */
		virtual void setSecondWorld(AbstractCoevolutionWorld& newSecondWorld);
		/**
		 * \brief Returns the combining results of the last calculation.
		 * \return The combining results.
		 */
		virtual const CombiningStrategyResults& getPrevResults() const;
		/**
		 * \brief Returns how often the first player has won in the last calculation.
		 * \return The amount of first player victories.
		 */
		virtual int getFirstPlayerWins() const;
		/**
		 * \brief Returns the total amount of matches in one calculation.
		 * \param simulationWorld The world which should be used for calculation.
		 * \return The total amount of matches.
		 */
		virtual int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const = 0;
	};
}

#endif
