#pragma once

#ifndef _ABSTRACTNEURALNETWORK_H_
#define _ABSTRACTNEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>
#include <ctime>

// Includes
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	class AbstractActivationOrder;
	class AbstractNeuron;
	class Vector;

	/**
	 * \brief All states which a neural network can be in.
	 */
	enum NeuralNetworkState
	{
		/**
		 * \brief The neural network is ready for training.
		 */
		NN_STATE_READY,
		/**
		 * \brief The network is currently being trained.
		 */
		NN_STATE_TRAINED,
	};

	/**
	 * \brief Describes a neural network which is the heart if LightBulb.
	 * \details The neural network is trained by learning rules. After that it can be used to calculated further results.
	 */
	class AbstractNeuralNetwork
	{
	private:
	public:
		virtual ~AbstractNeuralNetwork() {}
		/**
		 * \brief Clones the whole neural network.
		 * \return The cloned neural network.
		 */
		virtual AbstractNeuralNetwork* clone() const = 0;
		/**
		 * \brief Calculates from the given input and activation order the output of the neural network.
		 * \param input The input.
		 * \param output The variable were the output will be stored in.
		 * \param activationOrder The activation order which should be used when calculating.
		 * \param resetActivations Control if the activations should be resetted before calculating.
		 */
		virtual void calculate(const std::vector<double>& input, std::vector<double>& output, const AbstractActivationOrder &activationOrder, bool resetActivations = true) = 0;
		/**
		* \brief Calculates from the given input and activation order the output of the neural network.
		* \param input The input.
		* \param activationOrder The activation order which should be used when calculating.
		* \param resetActivations Control if the activations should be resetted before calculating.
		*/
		virtual std::vector<double> calculate(const std::vector<double>& input, const AbstractActivationOrder &activationOrder, bool resetActivations = true) = 0;
		/**
		* \brief Calculates from the given input and activation order the output of the neural network.
		* \param input The input.
		* \param activationOrder The activation order which should be used when calculating.
		* \param resetActivations Control if the activations should be resetted before calculating.
		*/
		virtual const Vector& calculateWithoutOutputCopy(const std::vector<double>& input, const AbstractActivationOrder &activationOrder, bool resetActivations = true) = 0;
		/**
		* \brief Calculates from the given input the output of the neural network.
		* \param input The input.
		* \param output The variable were the output will be stored in.
		* \param resetActivations Control if the activations should be resetted before calculating.
		* \note The default activation order of the network topology is taken for the calculation.
		*/
		virtual void calculate(const std::vector<double>& input, std::vector<double>& output, bool resetActivations = true) = 0;
		/**
		* \brief Calculates from the given input the output of the neural network.
		* \param input The input.
		* \param resetActivations Control if the activations should be resetted before calculating.
		* \note The default activation order of the network topology is taken for the calculation.
		*/
		virtual std::vector<double> calculate(const std::vector<double>& input, bool resetActivations = true) = 0;
		/**
		 * \brief Returns the network topology of the neural network.
		 * \return The network topology.
		 */
		virtual AbstractNetworkTopology& getNetworkTopology() const = 0;
		/**
		 * \brief Returns the name of the neural network.
		 * \return The name.
		 */
		virtual const std::string& getName() const = 0;
		/**
		 * \brief Sets the name of the neural network.
		 * \param name The name.
		 */
		virtual void setName(const std::string& name) = 0;
		/**
		 * \brief Returns the creation date of the neural network.
		 * \return The creation date.
		 */
		virtual const time_t& getCreationDate() const = 0;
		/**
		 * \brief Returns the current state of the neural network.
		 * \return The state.
		 */
		virtual const NeuralNetworkState& getState() const = 0;
		/**
		 * \brief Sets a new state.
		 * \param newState The new state.
		 */
		virtual void setState(NeuralNetworkState newState) = 0;
		/**
		 * \brief Returns the state as string.
		 * \return The state as string.
		 */
		virtual std::string getStateAsString() const;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractNeuralNetwork, LightBulb);


#endif
