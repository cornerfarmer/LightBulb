// Includes
#include "Windows/SimulatorWindow.hpp"
#include "SimulatorController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

SimulatorWindow::SimulatorWindow(SimulatorController* controller_, AbstractWindow* parent)
	:AbstractWindow("Simulator", parent)
{
	controller = controller_;

	sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

	header->Add(new wxStaticText(this, wxID_ANY, "Network:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	neuralNetworksChoice = new wxChoice(this, wxID_ANY);
	neuralNetworksChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&SimulatorWindow::networkChanged), this);

	header->Add(neuralNetworksChoice);
	sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);

	inputSizer = new wxBoxSizer(wxHORIZONTAL);
	outputSizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(this, wxID_ANY, "Input:"), 0, wxALL, 7);
	sizer->Add(inputSizer, 0, wxEXPAND | wxALL, 7);
	sizer->Add(new wxButton(this, wxID_ANY, "Neural network"), 1, wxALL | wxEXPAND, 7);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Output:"), 0, wxALL, 7);
	sizer->Add(outputSizer, 0, wxEXPAND | wxALL, 7);

	SetSizerAndFit(sizer);
}

void SimulatorWindow::networkChanged(wxCommandEvent& event)
{
	AbstractNeuralNetwork* network = (*controller->getNeuralNetworks())[event.GetSelection()];
	inputSizer->Clear(true);
	inputCheckBoxes.clear();
	inputSizer->AddStretchSpacer(1);
	for (int i = 0; i < network->getNetworkTopology()->getNeuronCountInLayer(0); i++)
	{
		inputCheckBoxes.push_back(new wxCheckBox(this, wxID_ANY, ""));
		inputCheckBoxes.back()->Bind(wxEVT_CHECKBOX, wxCommandEventFunction(&SimulatorWindow::selectionChanged), this);
		inputSizer->Add(inputCheckBoxes.back(), 0);
		inputSizer->AddStretchSpacer(1);
	}

	outputCheckBoxes.clear();
	outputSizer->Clear(true);
	outputSizer->AddStretchSpacer(1);
	for (int i = 0; i < network->getNetworkTopology()->getOutputSize(); i++)
	{
		outputCheckBoxes.push_back(new wxCheckBox(this, wxID_ANY, ""));
		outputCheckBoxes.back()->Enable(false);
		outputSizer->Add(outputCheckBoxes.back(), 0);
		outputSizer->AddStretchSpacer(1);
	}

	SetSizerAndFit(sizer);
	recalculateNetworkOutput();
}

void SimulatorWindow::recalculateNetworkOutput()
{
	std::vector<double> input(inputCheckBoxes.size());
	for (int i = 0; i < inputCheckBoxes.size(); i++)
		input[i] = inputCheckBoxes[i]->GetValue();

	std::vector<double> output = controller->calculate(neuralNetworksChoice->GetSelection(), input);

	for (int i = 0; i < outputCheckBoxes.size(); i++)
		outputCheckBoxes[i]->SetValue(output[i] > 0.5);
}

void SimulatorWindow::selectionChanged(wxCommandEvent& event)
{
	recalculateNetworkOutput();
}

void SimulatorWindow::refreshNeuralNetworks()
{
	neuralNetworksChoice->Clear();
	for (auto network = controller->getNeuralNetworks()->begin(); network != controller->getNeuralNetworks()->end(); network++)
	{
		neuralNetworksChoice->Append((*network)->getName());
	}
}
