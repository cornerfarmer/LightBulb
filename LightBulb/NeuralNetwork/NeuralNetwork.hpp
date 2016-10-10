#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>
#include <memory>

// Includes
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include <cereal/access.hpp>

namespace LightBulb
{
	// Forward declarations
	class AbstractActivationOrder;
	class AbstractNeuron;

	/**
	* \brief Describes a neural network which is the heart if LightBulb.
	* \details The neural network is trained by learning rules. After that it can be used to calculated further results.
	*/
	class NeuralNetwork : public AbstractNeuralNetwork
	{
		template <class Archive>
		friend void serialize(Archive& archive, NeuralNetwork& neuralNetwork);
		friend struct cereal::LoadAndConstruct<NeuralNetwork>;
	private:
		/**
		 * \brief The network topology which contains the structure of the network.
		 */
		std::unique_ptr<AbstractNetworkTopology> networkTopology;
		/**
		 * \brief The current state of the network.
		 */
		NeuralNetworkState state;
		/**
		 * \brief The name of the network.
		 */
		std::string name;
	public:
		/**
		 * \brief Create a new neural network.
		 * \param networkTopology_ The network topology of the new network.
		 */
		NeuralNetwork(AbstractNetworkTopology* networkTopology_);
		// Inherited:
		void calculate(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = NULL, bool resetActivations = true) override;
		void calculate(std::vector<double>& input, std::vector<double>& output, AbstractActivationOrder &activationOrder, bool resetActivations = true) override;
		AbstractNetworkTopology* getNetworkTopology() override;
		std::string getName() override;
		std::time_t getCreationDate() override;
		NeuralNetworkState getState() override;
		void setState(NeuralNetworkState newState) override;
		AbstractNeuralNetwork* clone() override;
		void setName(std::string name) override;
	};
}

#include "IO/NeuralNetworkIO.hpp"

#endif

