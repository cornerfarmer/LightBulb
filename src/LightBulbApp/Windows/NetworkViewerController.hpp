#pragma once

#ifndef _NETWORKVIEWERCONTROLLER_H_
#define _NETWORKVIEWERCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "NetworkViewerWindow.hpp"
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;
	class AbstractNeuralNetwork;
	/**
	 * \brief A sub app which visualizes a neural network.
	 * \details Draws neurons, their weights and their thresholds.
	 */
	class NetworkViewerController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding window.
		 */
		NetworkViewerWindow* window;
		/**
		 * \brief The neural network repository.
		 */
		NeuralNetworkRepository* neuralNetworkRepository;
	protected:
	public:
		/**
		 * \brief Creates the network viewer sub app.
		 * \param mainApp The main app which should manage the sub app.
		 * \param neuralNetworkRepository_ The neural network repository.
		 * \param parent The parent window.
		 */
		NetworkViewerController(AbstractMainApp& mainApp, NeuralNetworkRepository& neuralNetworkRepository_, AbstractWindow& parent);
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		NetworkViewerWindow& getWindow();
		/**
		 * \brief Returns all selectable neural networks.
		 * \return A vector with all network.
		 */
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& getNeuralNetworks() const;
		/**
		 * \brief Is called after the neural network repository has been changed.
		 * \param neuralNetworkRepository The neural network repository.
		 */
		void neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository);
		/**
		 * \brief Returns the label of the sub app.
		 * \return The label.
		 */
		static std::string getLabel();

	};
}

#endif
