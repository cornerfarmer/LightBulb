#pragma once

#ifndef _SIMULATORWINDOW_H_
#define _SIMULATORWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class SimulatorController;

class SimulatorWindow : public AbstractWindow
{
private:
	wxChoice* neuralNetworksChoice;
	SimulatorController* controller;
	wxBoxSizer* inputSizer;
	wxBoxSizer* outputSizer;
	wxPanel* panel;
	wxBoxSizer* sizer;
	std::vector<wxCheckBox*> inputCheckBoxes;
	std::vector<wxCheckBox*> outputCheckBoxes;
	void networkChanged(wxCommandEvent& event);
	void recalculateNetworkOutput();
	void selectionChanged(wxCommandEvent& event);
public:
	SimulatorWindow(SimulatorController* controller_, AbstractWindow* parent = NULL);
	void refreshNeuralNetworks();
};

#endif
