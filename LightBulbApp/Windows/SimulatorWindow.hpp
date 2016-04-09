#pragma once

#ifndef _SIMULATORWINDOW_H_
#define _SIMULATORWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class SimulatorController;
class AbstractNeuralNetwork;

class SimulatorWindow : public AbstractWindow
{
private:
	wxChoice* neuralNetworksChoice;
	SimulatorController* controller;
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
	void refreshInput(AbstractNeuralNetwork* network);
	void refreshOutput(AbstractNeuralNetwork* network);
public:
	SimulatorWindow(SimulatorController* controller_, AbstractWindow* parent = NULL);
	void refreshNeuralNetworks();
};

#endif
