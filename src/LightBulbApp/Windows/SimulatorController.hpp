#pragma once

#ifndef _SIMULATORCONTROLLER_H_
#define _SIMULATORCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "SimulatorWindow.hpp"
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingWindow;
	class TrainingController;
	class NeuralNetworkRepository;
	class AbstractNeuralNetwork;
	/**
	 * \brief A sub app which can simulate calculations on a neural network.
	 */
	class SimulatorController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding window.
		 */
		std::unique_ptr<SimulatorWindow> window;
		/**
		 * \brief The neural network repository to use.
		 */
		NeuralNetworkRepository* neuralNetworkRepository;
	protected:
		// Inherited:
		void prepareClose() override;
	public:
		/**
		* \brief Creates the simulator sub app.
		* \param mainApp The main app.
		* \param neuralNetworkRepository_ The neural network repository.
		* \param parent The parent window.
		*/
		SimulatorController(AbstractMainApp& mainApp, NeuralNetworkRepository& neuralNetworkRepository_, AbstractWindow& parent);
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		SimulatorWindow& getWindow();
		/**
		 * \brief Returns all selectable neural network.
		 * \return A vector of all networks.
		 */
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& getNeuralNetworks();
		/**
		* \brief Is called after the neural network repository has been changed.
		* \param neuralNetworkRepository The neural network repository.
		*/
		void neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository);
		/**
		 * \brief Calculates the output of the given network and the given input.
		 * \param neuralNetworkIndex The index of the network to use.
		 * \param input The input to use.
		 * \return The output.
		 */
		std::vector<double> calculate(int neuralNetworkIndex, const std::vector<double>& input);
		/**
		 * \brief Returns the label of the sup app.
		 * \return The label.
		 */
		static std::string getLabel();
	};
}

#endif
