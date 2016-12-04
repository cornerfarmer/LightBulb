#pragma once

#ifndef _ABSTRACTACTIVATIONFUNCTION_H_
#define _ABSTRACTACTIVATIONFUNCTION_H_

// Includes
#include "LightBulb/Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <Eigen/Cholesky>
#include <memory>

namespace LightBulb
{
	// Forward declaration
	class AbstractThreshold;

	/**
	 * \brief This abstract class describes a function, which can calculate the activation of a neuron from its input
	 */
	class AbstractActivationFunction : public virtual AbstractCloneable
	{
	private:
	public:
		virtual ~AbstractActivationFunction() {}
		/**
		 * \brief Calculate the activation from the given input for all neurons in one layer
		 * \param layerNr The layer number which should be considered
		 * \param activations A layerwise list of all activations which will contain the calculated activations
		 * \param netInputs A layerwise list of all inputs which will be used for the computation
		 */
		virtual void execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, const std::vector<Eigen::VectorXd> &netInputs) const;
		/**
		 * \brief Calculates the activation for one neuron
		 * \param input The input of the neuron
		 * \return The activation of the neuron
		 */
		virtual double execute(double input) const = 0;
		/**
		 * \brief Calculates the derivated activation from the given input
		 * \param input The input of the neuron
		 * \return The calculated activation derivation
		 */
		virtual double executeDerivation(double input) const = 0;
		/**
		 * \brief Calculate the derivated activation from the given input of every neuron for one layer
		 * \param input One layer of input values
		 * \return The calculated activation derivations for the whole layer
		 */
		virtual Eigen::VectorXd executeDerivation(const Eigen::VectorXd& input) const;
		/**
		 * \brief Returns the maximum possible output/activation value of this function
		 * \return The maximum
		 */
		virtual double getMaximum() const = 0;
		/**
		* \brief Returns the lowest possible output/activation value of this function
		* \return The minimum
		*/
		virtual double getMinimum() const = 0;
		/**
		 * \brief Returns if the function has an max/minimum.
		 * \return Max/minimum exists
		 */
		virtual bool hasAMaxAndMinimum() const = 0;
	};
}

#endif