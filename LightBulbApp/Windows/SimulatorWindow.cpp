// Includes
#include "Windows/SimulatorWindow.hpp"
#include "SimulatorController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <wx/valnum.h>

namespace LightBulb
{
	enum IOType
	{
		TYPE_BOOL,
		TYPE_FLOAT
	};

	SimulatorWindow::SimulatorWindow(SimulatorController& controller_, AbstractWindow& parent)
		:AbstractSubAppWindow(controller_, SimulatorController::getLabel(), parent)
	{
		sizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

		header->Add(new wxStaticText(this, wxID_ANY, "Network:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		neuralNetworksChoice = new wxChoice(this, wxID_ANY);
		neuralNetworksChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&SimulatorWindow::networkChanged), this);

		header->Add(neuralNetworksChoice);
		sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);

		inputSizer = new wxBoxSizer(wxHORIZONTAL);
		outputSizer = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer* inputHeader = new wxBoxSizer(wxHORIZONTAL);
		inputHeader->Add(new wxStaticText(this, wxID_ANY, "Input:"), 0, wxALL, 7);
		inputHeader->AddStretchSpacer(1);
		inputTypeChoice = new wxChoice(this, wxID_ANY);
		inputTypeChoice->Append("Boolean");
		inputTypeChoice->Append("Floating");
		inputTypeChoice->SetSelection(0);
		inputTypeChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&SimulatorWindow::inputTypeChanged), this);
		inputHeader->Add(inputTypeChoice, 0, wxALL, 7);
		sizer->Add(inputHeader, 0, wxEXPAND);

		sizer->Add(inputSizer, 0, wxEXPAND | wxALL, 7);
		sizer->Add(new wxButton(this, wxID_ANY, "Neural network"), 1, wxALL | wxEXPAND, 7);

		wxBoxSizer* outputHeader = new wxBoxSizer(wxHORIZONTAL);
		outputHeader->Add(new wxStaticText(this, wxID_ANY, "Output:"), 0, wxALL, 7);
		outputHeader->AddStretchSpacer(1);
		outputTypeChoice = new wxChoice(this, wxID_ANY);
		outputTypeChoice->Append("Boolean");
		outputTypeChoice->Append("Floating");
		outputTypeChoice->SetSelection(0);
		outputTypeChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&SimulatorWindow::outputTypeChanged), this);
		outputHeader->Add(outputTypeChoice, 0, wxALL, 7);
		sizer->Add(outputHeader, 0, wxEXPAND);

		sizer->Add(outputSizer, 0, wxEXPAND | wxALL, 7);

		SetSizerAndFit(sizer);
	}

	void SimulatorWindow::networkChanged(wxCommandEvent& event)
	{
		AbstractNeuralNetwork* network = getController().getNeuralNetworks()[event.GetSelection()].get();

		refreshInput(*network);
		refreshOutput(*network);
		recalculateNetworkOutput();

		refreshAfterChange(*sizer);
	}

	void SimulatorWindow::recalculateNetworkOutput()
	{
		IOType inputType = static_cast<IOType>(inputTypeChoice->GetSelection());
		std::vector<double> input(inputControls.size());
		for (int i = 0; i < inputControls.size(); i++)
		{
			if (inputType == TYPE_BOOL)
			{
				input[i] = static_cast<wxCheckBox*>(inputControls[i])->GetValue();
			}
			else if (inputType == TYPE_FLOAT)
			{
				try
				{
					input[i] = std::stod(static_cast<wxTextCtrl*>(inputControls[i])->GetValue().ToStdString());
				}
				catch (std::invalid_argument e)
				{
					input[i] = 0;
				}
			}
		}

		IOType outputType = static_cast<IOType>(outputTypeChoice->GetSelection());
		std::vector<double> output = getController().calculate(neuralNetworksChoice->GetSelection(), input);

		for (int i = 0; i < outputControls.size(); i++)
		{
			if (outputType == TYPE_BOOL)
			{
				static_cast<wxCheckBox*>(outputControls[i])->SetValue(output[i] > 0.5);
			}
			else if (outputType == TYPE_FLOAT)
			{
				static_cast<wxTextCtrl*>(outputControls[i])->SetValue(std::to_string(output[i]));
			}
		}
	}

	void SimulatorWindow::selectionChanged(wxCommandEvent& event)
	{
		recalculateNetworkOutput();
	}

	void SimulatorWindow::inputTypeChanged(wxCommandEvent& event)
	{
		AbstractNeuralNetwork* network = getController().getNeuralNetworks()[neuralNetworksChoice->GetSelection()].get();
		refreshInput(*network);
		recalculateNetworkOutput();

		refreshAfterChange(*sizer);
	}

	void SimulatorWindow::outputTypeChanged(wxCommandEvent& event)
	{
		AbstractNeuralNetwork* network = getController().getNeuralNetworks()[neuralNetworksChoice->GetSelection()].get();
		refreshOutput(*network);
		recalculateNetworkOutput();

		refreshAfterChange(*sizer);
	}

	void SimulatorWindow::refreshInput(AbstractNeuralNetwork& network)
	{
		IOType type = static_cast<IOType>(inputTypeChoice->GetSelection());

		inputSizer->Clear(true);
		inputControls.clear();
		inputSizer->AddStretchSpacer(1);
		for (int i = 0; i < network.getNetworkTopology().getInputSize(); i++)
		{
			if (type == TYPE_BOOL)
			{
				inputControls.push_back(new wxCheckBox(this, wxID_ANY, "", wxPoint(-100, -100)));
				inputControls.back()->Bind(wxEVT_CHECKBOX, wxCommandEventFunction(&SimulatorWindow::selectionChanged), this);
				inputSizer->Add(inputControls.back(), 0);
			}
			else if (type == TYPE_FLOAT)
			{
				inputControls.push_back(new wxTextCtrl(this, wxID_ANY, "0", wxPoint(-100, -100), wxSize(60, -1)));
				wxFloatingPointValidator<double> val(3);
				inputControls.back()->SetValidator(val);
				inputControls.back()->Bind(wxEVT_TEXT, wxCommandEventFunction(&SimulatorWindow::selectionChanged), this);
				inputSizer->Add(inputControls.back(), 0);
			}
			inputSizer->AddStretchSpacer(1);
		}

	}

	void SimulatorWindow::refreshOutput(AbstractNeuralNetwork& network)
	{
		IOType type = static_cast<IOType>(outputTypeChoice->GetSelection());

		outputControls.clear();
		outputSizer->Clear(true);
		outputSizer->AddStretchSpacer(1);
		for (int i = 0; i < network.getNetworkTopology().getOutputSize(); i++)
		{
			if (type == TYPE_BOOL)
			{
				outputControls.push_back(new wxCheckBox(this, wxID_ANY, "", wxPoint(-100, -100)));
				outputControls.back()->Enable(false);
			}
			else if (type == TYPE_FLOAT)
			{
				outputControls.push_back(new wxTextCtrl(this, wxID_ANY, "0", wxPoint(-100, -100), wxSize(60, -1)));
				outputControls.back()->Enable(false);
			}
			outputSizer->Add(outputControls.back(), 0);
			outputSizer->AddStretchSpacer(1);
		}

	}

	SimulatorController& SimulatorWindow::getController()
	{
		return static_cast<SimulatorController&>(*controller);
	}

	void SimulatorWindow::refreshNeuralNetworks()
	{
		neuralNetworksChoice->Clear();
		for (auto network = getController().getNeuralNetworks().begin(); network != getController().getNeuralNetworks().end(); network++)
		{
			neuralNetworksChoice->Append((*network)->getName());
		}
	}
}