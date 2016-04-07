// Includes
#include "Windows/LearningStateWindow.hpp"
#include "LearningStateController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>
#include <string>
#include <wx/valnum.h>

wxDEFINE_EVENT(LSW_EVT_REFRESH_CHART, wxThreadEvent);

LearningStateWindow::LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent)
	:AbstractWindow("LearningState", parent)
{
	controller = controller_;

	Bind(LSW_EVT_REFRESH_CHART, wxThreadEventFunction(&LearningStateWindow::refreshChart), this);

	sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

	header->Add(new wxStaticText(this, wxID_ANY, "Learning plan:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	trainingPlansChoice = new wxChoice(this, wxID_ANY);
	trainingPlansChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LearningStateWindow::trainingPlanChanged), this);

	header->Add(trainingPlansChoice);
	sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);

	wxBoxSizer* body = new wxBoxSizer(wxHORIZONTAL);

	dataSetsSizer = new wxBoxSizer(wxVERTICAL);

	body->Add(dataSetsSizer, 0, wxALL, 7);

	
	chartPanel = new wxChartPanel(this, wxID_ANY, NULL, wxDefaultPosition, wxSize(100, 100));
	chartPanel->SetMinSize(wxSize(500, 300));

	body->Add(chartPanel, 1, wxEXPAND);

	sizer->Add(body, 1, wxEXPAND);

	wxBoxSizer* footer = new wxBoxSizer(wxHORIZONTAL);

	footer->Add(new wxStaticText(this, wxID_ANY, "Refresh all "), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	refreshRateChoice = new wxComboBox(this, wxID_ANY);
	wxIntegerValidator<unsigned int> validator;
	validator.SetMin(1);
	validator.SetMax(1000000);
	refreshRateChoice->SetValue(std::to_string(controller->getRefreshRate()));
	refreshRateChoice->SetValidator(validator);
	refreshRateChoice->Append("1");
	refreshRateChoice->Append("5");
	refreshRateChoice->Append("20");
	refreshRateChoice->Append("50");
	refreshRateChoice->Append("100");
	refreshRateChoice->Append("200");
	refreshRateChoice->Append("500");
	refreshRateChoice->Append("1000");
	refreshRateChoice->Bind(wxEVT_COMBOBOX, wxCommandEventFunction(&LearningStateWindow::refreshRateChanged), this);
	refreshRateChoice->Bind(wxEVT_TEXT, wxCommandEventFunction(&LearningStateWindow::refreshRateChanged), this);
	footer->Add(refreshRateChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	footer->Add(new wxStaticText(this, wxID_ANY, " iterations."), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

	sizer->Add(footer, 0, wxALL, 7);
	
	SetSizerAndFit(sizer);
}

void LearningStateWindow::trainingPlanChanged(wxCommandEvent& event)
{
	controller->setSelectedTrainingPlan(event.GetSelection());
	dataSetsSizer->Clear();
	dataSetsSizer->Add(new wxStaticText(this, wxID_ANY, "Datasets:"));

	std::vector<std::string> dataSetLabels = controller->getSelectedTrainingPlan()->getDataSetLabels();
	for (auto label = dataSetLabels.begin(); label != dataSetLabels.end(); label++)
	{
		dataSetsCheckBoxes.push_back(new wxCheckBox(this, wxID_ANY, *label));
		dataSetsCheckBoxes.back()->Bind(wxEVT_CHECKBOX, wxCommandEventFunction(&LearningStateWindow::selectionChanged), this);
		dataSetsSizer->Add(dataSetsCheckBoxes.back());
	}

	Fit();
}

void LearningStateWindow::refreshRateChanged(wxCommandEvent& event)
{
	try
	{
		controller->setRefreshRate(std::stoi(refreshRateChoice->GetValue().ToStdString()));
	}
	catch(std::invalid_argument e)
	{
		
	}
}

void LearningStateWindow::selectionChanged(wxCommandEvent& event)
{
	wxThreadEvent evt;
	refreshChart(evt);
}


void LearningStateWindow::refreshTrainingPlans()
{
	trainingPlansChoice->Clear();
	for (auto network = controller->getTrainingPlans()->begin(); network != controller->getTrainingPlans()->end(); network++)
	{
		trainingPlansChoice->Append((*network)->getName());
	}
}

void LearningStateWindow::refreshChart(wxThreadEvent& event)
{
	// first step: create plot
	XYPlot* plot = new XYPlot();
	// create dataset
	XYSimpleDataset *dataset = new XYSimpleDataset();

	for (auto checkBox = dataSetsCheckBoxes.begin(); checkBox != dataSetsCheckBoxes.end(); checkBox++)
	{
		if ((*checkBox)->IsChecked())
		{
			std::vector<double>* dataSet = controller->getDataSet((*checkBox)->GetLabel().ToStdString());

			if (dataSet->size() > 0)
			{
				// and add serie to it
				dataset->AddSerie(&(*dataSet)[0], dataSet->size() / 2);

				// set line renderer to dataset
				dataset->SetRenderer(new XYLineRenderer());

				dataset->SetSerieName(dataset->GetSerieCount() - 1, (*checkBox)->GetLabel());
			}
		}
	}

	if (dataset->GetSerieCount() > 0)
	{
		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// optional: set axis titles
		leftAxis->SetTitle("Value");
		leftAxis->SetFixedBounds(0, dataset->GetMaxY());
		bottomAxis->SetTitle("Iterations");

		// add axes and dataset to plot
		plot->AddObjects(dataset, leftAxis, bottomAxis);

		// set legend
		plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

		// and finally create chart
		Chart* chart = new Chart(plot, controller->getSelectedTrainingPlan()->getName());
		chartPanel->SetChart(chart);
	}

	controller->refreshFinished();
}
