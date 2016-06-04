// Includes
#include "Windows/NetworkViewerWindow.hpp"
#include "NetworkViewerController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

BEGIN_EVENT_TABLE(NetworkViewerWindow, wxFrame)
EVT_PAINT(NetworkViewerWindow::paintEvent)
EVT_SIZE(NetworkViewerWindow::resize)
END_EVENT_TABLE()

#define BORDER 30

NetworkViewerWindow::NetworkViewerWindow(NetworkViewerController* controller_, AbstractWindow* parent)
	:AbstractSubAppWindow(controller_, NetworkViewerController::getLabel(), parent)
{

	selectedNetwork = NULL;

	sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

	header->Add(new wxStaticText(this, wxID_ANY, "Network:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	neuralNetworksChoice = new wxChoice(this, wxID_ANY);
	neuralNetworksChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&NetworkViewerWindow::networkChanged), this);

	header->Add(neuralNetworksChoice);
	sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);

	panel = new wxScrolledWindow(this);
	
	panel->SetMinSize(wxSize(300, 300));
	panel->Bind(wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventFunction(&NetworkViewerWindow::scrollEvent), this);
	panel->Bind(wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventFunction(&NetworkViewerWindow::scrollEvent), this);

	sizer->Add(panel, 1, wxEXPAND);

	SetSizerAndFit(sizer);

}


void NetworkViewerWindow::scrollEvent(wxScrollWinEvent& event)
{
	paintNow();
	event.Skip();
}

void NetworkViewerWindow::networkChanged(wxCommandEvent& event)
{
	selectedNetwork = (*getController()->getNeuralNetworks())[event.GetSelection()].get();
	
	auto neuronCountsPerLayer = selectedNetwork->getNetworkTopology()->getNeuronCountsPerLayer();

	int layerCount = neuronCountsPerLayer.size();
	unsigned int maxNeuronCount = 0;
	for (int i = 0; i < neuronCountsPerLayer.size(); i++)
		maxNeuronCount = std::max(maxNeuronCount, neuronCountsPerLayer[i]);

	panel->SetScrollbars(1, 1, layerCount * 60, maxNeuronCount * 60, 0, 0);

	paintNow();
}


NetworkViewerController* NetworkViewerWindow::getController()
{
	return static_cast<NetworkViewerController*>(controller);
}


void NetworkViewerWindow::paintEvent(wxPaintEvent& evt)
{
	paintNow();
}

void NetworkViewerWindow::resize(wxSizeEvent& evt)
{
	Layout();
	paintNow();
}

void NetworkViewerWindow::paintNow()
{
	if (panel)
	{
		wxClientDC dc(panel);
		render(dc);
	}
}

void NetworkViewerWindow::render(wxDC& dc)
{
	if (selectedNetwork)
	{
		dc.SetBackground(*wxWHITE_BRUSH);
		dc.SetBackgroundMode(wxSOLID);

		dc.Clear();

		panel->GetVirtualSize(&width, &height);
		panel->GetScrollPos(0);

		layerCount = selectedNetwork->getNetworkTopology()->getLayerCount();
		for (int l = 0; l < layerCount; l++)
		{
			int neuronCount = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l);
			for (int n = 0; n < neuronCount; n++)
			{
				dc.DrawCircle(getXPos(l), getYPos(n, neuronCount), 20);
			}
		}

		auto weights = selectedNetwork->getNetworkTopology()->getWeights();
		bool usesBiasNeuron = selectedNetwork->getNetworkTopology()->usesBiasNeuron();

		for (int l = 0; l < weights->size(); l++)
		{
			int neuronCount = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l);
			int neuronCountNextLayer = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l + 1);
			for (int tn = 0; tn < (*weights)[l].rows(); tn++)
			{
				for (int fn = usesBiasNeuron; fn < (*weights)[l].cols(); fn++)
				{
					dc.DrawLine(getXPos(l), getYPos(fn - usesBiasNeuron, neuronCount), getXPos(l + 1), getYPos(tn, neuronCountNextLayer));
				}
			}
		}

	}
}

int NetworkViewerWindow::getXPos(int layerIndex)
{	
	float spacePartsBefore = layerCount > 1 ? 1.0 / (layerCount - 1) * layerIndex : 0.5;
	return (width - 2 * BORDER) * spacePartsBefore + BORDER - panel->GetScrollPos(wxHORIZONTAL);
}


int NetworkViewerWindow::getYPos(int neuronIndex, int neuronCount)
{
	float spacePartsBefore = neuronCount > 1 ? 1.0 / (neuronCount - 1) * neuronIndex : 0.5;
	return (height - 2 * BORDER) * spacePartsBefore + BORDER - panel->GetScrollPos(wxVERTICAL);
}

void NetworkViewerWindow::refreshNeuralNetworks()
{
	neuralNetworksChoice->Clear();
	for (auto network = getController()->getNeuralNetworks()->begin(); network != getController()->getNeuralNetworks()->end(); network++)
	{
		neuralNetworksChoice->Append((*network)->getName());
	}
}
