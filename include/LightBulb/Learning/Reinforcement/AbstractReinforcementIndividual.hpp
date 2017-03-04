#pragma once

#ifndef _ABSTRACTREINFORCEMENTINDIVIDUAL_H_
#define _ABSTRACTREINFORCEMENTINDIVIDUAL_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	struct LearningState;
	class NeuralNetwork;
	/**
	 * \brief Describes the environment where the reinforcement learning process takes places.
	 */
	class AbstractReinforcementIndividual : public virtual AbstractRandomGeneratorUser, public virtual AbstractLinearAlgebraUser
	{
	protected:
		/**
		* \brief Executes the neural network calculation.
		*/
		virtual void doNNCalculation() = 0;
	public:
		virtual void initializeKernels() = 0;
		/**
		* \brief Executes one simulation step.
		* \return Returns the reward gained after that step.
		*/
		virtual void doSimulationStep();
		/**
		* \brief Initializes the environment before the learning starts.
		*/
		virtual void initializeForLearning() = 0;
		/**
		 * \brief Can be used to rate the current AI for debugging purposes.
		 * \return The rating.
		 */
		virtual int rate() { return 0; };
		/**
		 * \brief Returns the neural network.
		 * \return The neural network.
		 */
		virtual NeuralNetwork& getNeuralNetwork() = 0;
		/**
		 * \brief Sets a new epsilon value.
		 * \param newEpsilon The new epsilon value.
		 */
		virtual void setEpsilon(double newEpsilon) = 0;
		/**
		 * \brief Returns the epsilon value.
		 * \return The epsilon value.
		 */
		virtual double getEpsilon() = 0;
		/**
		 * \brief Returns the last chosen actions of the network.
		 * \return A vector of bools which tell per actions if they were taken.
		 */
		virtual const Vector<char>& getLastBooleanOutput() const = 0;
		virtual const Vector<>& getLastInput() const = 0;
		/**
		 * \brief Sets, if actions should be taken randomly. 
		 * \param useStochasticActionDecision_ True, if actions should be taken randomly. 
		 */
		virtual void setStochasticActionDecision(bool useStochasticActionDecision_) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractReinforcementIndividual, LightBulb);

#endif
