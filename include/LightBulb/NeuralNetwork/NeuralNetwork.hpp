#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <memory>
#include <cereal/access.hpp>

// Includes
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"

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
		time_t creationTime;
	public:
		/**
		 * \brief Create a new neural network.
		 * \param networkTopology_ The network topology of the new network.
		 */
		NeuralNetwork(AbstractNetworkTopology* networkTopology_);
		~NeuralNetwork();
		// Inherited:
		void calculate(const std::vector<double>& input, std::vector<double>& output, const AbstractActivationOrder &activationOrder, bool resetActivations = true) override;
		std::vector<double> calculate(const std::vector<double>& input, const AbstractActivationOrder& activationOrder, bool resetActivations = true) override;
		void calculate(const std::vector<double>& input, std::vector<double>& output, bool resetActivations = true) override;
		std::vector<double> calculate(const std::vector<double>& input, bool resetActivations = true) override;
		const Vector<>& calculateWithoutOutputCopy(const Vector<>& input, const AbstractActivationOrder &activationOrder, bool resetActivations) override;
		AbstractNetworkTopology& getNetworkTopology() const override;
		const std::string& getName() const override;
		const time_t& getCreationDate() const override;
		const NeuralNetworkState& getState() const override;
		void setState(NeuralNetworkState newState) override;
		AbstractNeuralNetwork* clone() const override;
		void setName(const std::string& name) override;
	};
}

#include "LightBulb/IO/NeuralNetworkIO.hpp"

#endif

