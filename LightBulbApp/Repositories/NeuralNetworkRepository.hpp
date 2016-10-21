#pragma once

#ifndef _NEURALNETWORKREPOSITORY_H_
#define _NEURALNETWORKREPOSITORY_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <Event/Observable.hpp>
#include <memory>

// Includes

namespace LightBulb
{
	// Forward declarations

	/**
	* \brief All observable events of NeuralNetworkRepository.
	*/
	enum NeuralNetworkRepositoryEvents
	{
		/**
		* \brief Is thrown when a new network has been added or an existing network has been removed.
		*/
		EVT_NN_CHANGED
	};

	/**
	 * \brief A repository which stores all neural networks which are currently trained in the LightBulbApp.
	 */
	class NeuralNetworkRepository : public LightBulb::Observable<NeuralNetworkRepositoryEvents, NeuralNetworkRepository>
	{
		template <class Archive>
		friend void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository);
	private:
		/**
		 * \brief All neural networks which are currently trained.
		 */
		std::vector<std::unique_ptr<AbstractNeuralNetwork>> neuralNetworks;
	public:
		/**
		 * \brief Creates a new neural network repository.
		 */
		NeuralNetworkRepository();
		/**
		 * \brief Returns all neural network.
		 * \return A vector of all neural networks.
		 */
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& getNeuralNetworks() const;
		/**
		 * \brief Returns the index of a given neural network.
		 * \param network The neural network.
		 * \return The index of the neural network in the network storage vector.
		 */
		int getIndexOfNeuralNetwork(const AbstractNeuralNetwork& network) const;
		/**
		 * \brief Adds a new neural network to the storage.
		 * \param neuralNetwork The new neural network.
		 */
		void Add(AbstractNeuralNetwork* neuralNetwork);
		/**
		 * \brief Saves the network with the given index as a file.
		 * \param path The path where to store the file.
		 * \param neuralNetworkIndex The index of the neural network to save.
		 */
		void save(const std::string& path, int neuralNetworkIndex) const;
		/**
		 * \brief Loads a neural network from file and stores it in the repository.
		 * \param path The path of the file to load.
		 */
		void load(const std::string& path);
	};
}

#include "IO/NeuralNetworkRepositoryIO.hpp"

#endif
