#pragma once

#ifndef _ABSTRACTNEURALNETWORK_H_
#define _ABSTRACTNEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>
#include <ctime>

// Includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	class AbstractActivationOrder;
	class AbstractNeuron;

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
		 * \param startTime The offset time where the calculation should start.
		 * \param timeStepCount How many time steps the calculation should be done.
		 * \param outputValuesInTime A variable which will contain all output values for all timesteps.
		 * \param netInputValuesInTime A variable which will contain all net inputs for all timesteps.
		 * \param resetActivations Control if the activations should be resetted before calculating.
		 * TODO: Refactor
		 */
		virtual void calculate(const std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, const AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = nullptr, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = nullptr, bool resetActivations = true) = 0;
		/**
		 * \brief Calculates from the given input and activation order the output of the neural network.
		 * \param input The input.
		 * \param output The variable were the output will be stored in.
		 * \param activationOrder The activation order which should be used when calculating.
		 * \param resetActivations Control if the activations should be resetted before calculating.
		 */
		virtual void calculate(const std::vector<double>& input, std::vector<double>& output, const AbstractActivationOrder &activationOrder, bool resetActivations = true) = 0;
		/**
		 * \brief Returns the network topology of the neural network.
		 * \return The network topology.
		 */
		virtual AbstractNetworkTopology* getNetworkTopology() const = 0;
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
		virtual const std::time_t& getCreationDate() const = 0;
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
		virtual const std::string getStateAsString() const;
	};
}

#endif
