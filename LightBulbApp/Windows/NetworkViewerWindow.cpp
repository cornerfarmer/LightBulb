// Includes
#include "Windows/NetworkViewerWindow.hpp"
#include "NetworkViewerController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

BEGIN_EVENT_TABLE(NetworkViewerWindow, wxFrame)
EVT_PAINT(NetworkViewerWindow::paintEvent)
EVT_SIZE(NetworkViewerWindow::resize)
END_EVENT_TABLE()

#define BORDER 40
#define NEURON_RAD 30
#define NEURON_SPACE 120
#define LAYER_SPACE 120
#define WEIGHT_SPACE 40

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

	panel->SetScrollbars(1, 1, layerCount * LAYER_SPACE, maxNeuronCount * NEURON_SPACE, 0, 0);

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
		dc.SetBackgroundMode(wxTRANSPARENT);
		dc.SetFont(*wxSMALL_FONT);

		dc.Clear();

		panel->GetVirtualSize(&width, &height);
		panel->GetScrollPos(0);


		auto weights = selectedNetwork->getNetworkTopology()->getWeights();
		bool usesBiasNeuron = selectedNetwork->getNetworkTopology()->usesBiasNeuron();

		layerCount = selectedNetwork->getNetworkTopology()->getLayerCount();
		for (int l = 0; l < layerCount; l++)
		{
			int neuronCount = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l);
			for (int n = 0; n < neuronCount; n++)
			{
				dc.DrawCircle(getXPos(l), getYPos(n, neuronCount), NEURON_RAD);

				if (usesBiasNeuron && l > 0)
				{
					double bias = (*weights)[l - 1](n, 0);
					wxCoord textWidth, textHeight;
					dc.GetTextExtent(std::to_string(bias), &textWidth, &textHeight);
					dc.DrawText(std::to_string(bias), getXPos(l) - textWidth / 2, getYPos(n, neuronCount) - textHeight / 2);
				}
			}
		}

		for (int l = 0; l < weights->size(); l++)
		{
			int neuronCount = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l);
			int neuronCountNextLayer = selectedNetwork->getNetworkTopology()->getNeuronCountInLayer(l + 1);
			for (int tn = 0; tn < (*weights)[l].rows(); tn++)
			{
				for (int fn = usesBiasNeuron; fn < (*weights)[l].cols(); fn++)
				{
					int x1 = getXPos(l);
					int y1 = getYPos(fn - usesBiasNeuron, neuronCount);
					int x2 = getXPos(l + 1);
					int y2 = getYPos(tn, neuronCountNextLayer);
					float angle = atan((float)(y2 - y1) / (x2 - x1));

					dc.DrawLine(x1 + NEURON_RAD * std::cos(angle), y1 + NEURON_RAD * std::sin(angle), x2 + NEURON_RAD * std::cos(angle + M_PI), y2 + NEURON_RAD * std::sin(angle + M_PI));

					dc.DrawRotatedText(std::to_string((*weights)[l](tn, fn)), x1 + WEIGHT_SPACE * std::cos(angle), y1 + WEIGHT_SPACE * std::sin(angle), -1 * angle / M_PI * 180);
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
