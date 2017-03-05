#pragma once

#ifndef _ABSTRACTREINFORCEMENTENVIRONMENT_H_
#define _ABSTRACTREINFORCEMENTENVIRONMENT_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	struct FeedForwardNetworkTopologyOptions;
	struct LearningState;
	class NeuralNetwork;
	class Kernel;
	/**
	 * \brief Describes the environment where the reinforcement learning process takes places.
	 */
	class AbstractReinforcementEnvironment : public virtual AbstractRandomGeneratorUser, public virtual AbstractLinearAlgebraUser
	{
	private:
	protected:
		/**
		 * \brief Points to the learning state of the learning rule.
		 */
		LearningState* learningState;
	public:
		~AbstractReinforcementEnvironment();
		/**
		* \brief Executes one simulation step.
		* \return Returns the reward gained after that step.
		*/
		virtual void doSimulationStep() = 0;
		virtual void prepareSimulationStep() {};
		/**
		* \brief Initializes the environment before the learning starts.
		*/
		virtual void initializeForLearning();
		/**
		 * \brief Sets the learning state.
		 * \param learningState_ The learning state.
		 */
		void setLearningState(LearningState& learningState_);
		/**
		* \brief Returns a vector of all data set labels which are available in the learning state of this learning rule.
		* \return The labels of all available data sets.
		*/
		virtual std::vector<std::string> getDataSetLabels() const;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractReinforcementEnvironment, LightBulb);

#endif
