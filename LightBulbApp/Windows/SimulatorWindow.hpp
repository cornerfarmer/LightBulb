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

	class SimulatorWindow : public AbstractSubAppWindow
	{
	private:
		wxChoice* neuralNetworksChoice;
		wxBoxSizer* inputSizer;
		wxBoxSizer* outputSizer;
		wxPanel* panel;
		wxBoxSizer* sizer;
		std::vector<wxControl*> inputControls;
		std::vector<wxControl*> outputControls;
		wxChoice* inputTypeChoice;
		wxChoice* outputTypeChoice;
		void networkChanged(wxCommandEvent& event);
		void recalculateNetworkOutput();
		void selectionChanged(wxCommandEvent& event);
		void inputTypeChanged(wxCommandEvent& event);
		void outputTypeChanged(wxCommandEvent& event);
		void refreshInput(AbstractNeuralNetwork& network);
		void refreshOutput(AbstractNeuralNetwork& network);
		SimulatorController& getController();
	public:
		SimulatorWindow(SimulatorController& controller_, AbstractWindow& parent);
		void refreshNeuralNetworks();
	};
}

#endif
