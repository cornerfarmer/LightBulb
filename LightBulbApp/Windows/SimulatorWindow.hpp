#pragma once

#ifndef _SIMULATORWINDOW_H_
#define _SIMULATORWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

namespace LightBulb
{
	// Forward declarations
	class SimulatorController;
	class AbstractNeuralNetwork;
	/**
	 * \brief The window of the simulator sub app.
	 */
	class SimulatorWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief The choice to select the network which should be used.
		 */
		wxChoice* neuralNetworksChoice;
		/**
		 * \brief The sizer which contains all controls which manage the input values.
		 */
		wxBoxSizer* inputSizer;
		/**
		* \brief The sizer which contains all controls which manage the output values.
		*/
		wxBoxSizer* outputSizer;
		/**
		 * \brief The main sizer.
		 */
		wxBoxSizer* sizer;
		/**
		 * \brief A vector of all controls which manage the input values.
		 */
		std::vector<wxControl*> inputControls;
		/**
		* \brief A vector of all controls which manage the output values.
		*/
		std::vector<wxControl*> outputControls;
		/**
		 * \brief The choice to select the input type.
		 */
		wxChoice* inputTypeChoice;
		/**
		* \brief The choice to select the output type.
		*/
		wxChoice* outputTypeChoice;
		/**
		 * \brief Is called after the network selection has been changed.
		 * \param event The event data.
		 */
		void networkChanged(wxCommandEvent& event);
		/**
		 * \brief Recalculates the network output with the current configured input.
		 */
		void recalculateNetworkOutput();
		/**
		 * \brief Is called after the input selection has been changed.
		 * \param event The event data.
		 */
		void selectionChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after the input type selection has been changed.
		 * \param event The event data.
		 */
		void inputTypeChanged(wxCommandEvent& event);
		/**
		* \brief Is called after the output type selection has been changed.
		* \param event The event data.
		*/
		void outputTypeChanged(wxCommandEvent& event);
		/**
		* \brief Rebuilds the input controls from the given network.
		* \param network The current network which should be used.
		*/
		void refreshInput(AbstractNeuralNetwork& network);
		/**
		* \brief Rebuilds the output controls from the given network.
		* \param network The current network which should be used.
		*/
		void refreshOutput(AbstractNeuralNetwork& network);
		/**
		 * \brief Returns the corresponding controller.
		 * \return The controller
		 */
		SimulatorController& getController();
	public:
		/**
		 * \brief Creates the simulateor window.
		 * \param controller_ The corresponding controller.
		 * \param parent The parent window.
		 */
		SimulatorWindow(SimulatorController& controller_, AbstractWindow& parent);
		/**
		 * \brief Refreshes the neural networks choice.
		 */
		void refreshNeuralNetworks();
	};
}

#endif
