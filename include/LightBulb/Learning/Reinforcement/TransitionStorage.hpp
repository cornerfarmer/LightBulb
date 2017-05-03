#pragma once

#ifndef _TRANSITIONSTORAGE_H_
#define _TRANSITIONSTORAGE_H_

// Includes

// Library Includes
#include <vector>
#include <memory>
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

namespace LightBulb
{
	class AbstractNetworkTopology;
	class AbstractReinforcementIndividual;
	class Kernel;
	class AbstractReinforcementEnvironment;
	/**
	 * \brief Describes a transition used in the reinforcement learning process.
	 */
	class TransitionStorage : public virtual AbstractLinearAlgebraUser
	{
	private:
		std::unique_ptr<Kernel> determineActionKernel;
		/**
		 * \brief The initial state.
		 */
		Matrix<> states;
		/**
		 * \brief The taken action.
		 */
		Vector<int> actions;
		/**
		 * \brief True, if transition ends in terminal state.
		 */
		Vector<char> isTerminalState;
		/**
		 * \brief The following state.
		 */
		Matrix<> nextStates;
		/**
		 * \brief The gained reward.
		 */
		Vector<> rewards;
		/**
		* \brief Index of the transition slot that should be used for the next new transition.
		*/
		int nextTransitionIndex;
		/**
		* \brief The current amount of stored transitions.
		*/
		int transitionCounter;
		int memorySize;
		/**
		* \brief Temporarily stores the current terminal state.
		*/
		Scalar<char> isTerminalStateTmp;
		/**
		* \brief Temporarily stores an input vector.
		*/
		Vector<> inputTemp;
		bool replaceStoredTransitions;
	public:
		~TransitionStorage();
		TransitionStorage();
		/**
		 * \brief Resets and resizes data structures.
		 * \param maxRecordNumber The maximum number of records.
		 * \param networkInputSize The input size.
		 */
		void reset(int maxRecordNumber, int networkInputSize, bool replaceStoredTransitions_);
		/**
		* \brief Stores the last transition into the replay memory.
		* \param networkTopology The network topology which was used.
		* \param reward The reward that was gained through this transition.
		*/
		void storeTransition(const ::LightBulb::AbstractReinforcementIndividual& individual, const AbstractReinforcementEnvironment& environment, const Scalar<>& reward);

		int getTransitionCounter() const;
		const Matrix<>& getStates() const;
		const Vector<int>& getActions() const;
		const Vector<char>& getIsTerminalState() const;
		const Matrix<>& getNextStates() const;
		const Vector<>& getRewards() const;
	};
}


#endif
