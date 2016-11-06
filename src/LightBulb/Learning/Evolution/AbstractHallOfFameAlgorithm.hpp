#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHM_H_
#define _ABSTRACTHALLOFFAMEALGORITHM_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Logging/AbstractLoggable.hpp"
#include "AbstractEvolutionObject.hpp"
#include "AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionWorld;
	/**
	 * \brief Describes an algorithm which stores some good objects of the time to make sure their knowledge will not be lost.
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
		 * \brief The current world to use for simulations.
		 */
		AbstractCoevolutionWorld* currentWorld;
		/**
		 * \brief All members of the hall of fame.
		 */
		std::vector<std::unique_ptr<AbstractEvolutionObject>> members;
		/**
		 * \brief Compares the given object with one memeber of the hall of fame.
		 * \param object The object to evaluate.
		 * \param memberID The id of the member to use.
		 * \param round The round number.
		 */
		void simulateAgainstMember(AbstractEvolutionObject& object, int memberID, int round);
		/**
		 * \brief Evaluates the given objects.
		 * \param objects A vector of objects.
		 */
		virtual void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) = 0;
	public:
		/**
		 * \brief Compares objects from the given world with members of the hall of fame.
		 * \param world The world to use.
		 * \param prevResults The CombiningStrategyResults where the new results should be stored in.
		 */
		virtual void execute(AbstractCoevolutionWorld& world, CombiningStrategyResults& prevResults);
		/**
		 * \brief Adds the given object to the hall of fame.
		 * \param newMember The new member to add.
		 */
		virtual void addMember(AbstractEvolutionObject* newMember);
	};
}

#include "IO/AbstractHallOfFameAlgorithmIO.hpp"

#endif
