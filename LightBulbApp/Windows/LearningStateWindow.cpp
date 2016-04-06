// Includes
#include "Windows/LearningStateWindow.hpp"
#include "LearningStateController.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>

LearningStateWindow::LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent)
	:AbstractWindow("LearningState", parent)
{
	controller = controller_;

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

	header->Add(new wxStaticText(this, wxID_ANY, "Network:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
	trainingPlansChoice = new wxChoice(this, wxID_ANY);
	trainingPlansChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LearningStateWindow::trainingPlanChanged), this);

	header->Add(trainingPlansChoice);
	sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);


	// serie xy data
	double data[][2] = {
		{ 10, 20, },
		{ 13, 16, },
		{ 7, 30, },
		{ 15, 34, },
		{ 25, 4, },
	};

	// first step: create plot
	XYPlot *plot = new XYPlot();

	// create dataset
	XYSimpleDataset *dataset = new XYSimpleDataset();

	// and add serie to it
	dataset->AddSerie((double *)data, WXSIZEOF(data));

	// set line renderer to dataset
	dataset->SetRenderer(new XYLineRenderer());

	// create left and bottom number axes
	NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
	NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

	// optional: set axis titles
	leftAxis->SetTitle(wxT("X"));
	bottomAxis->SetTitle(wxT("Y"));

	// add axes and dataset to plot
	plot->AddObjects(dataset, leftAxis, bottomAxis);

	// and finally create chart
	Chart* chart = new Chart(plot, "T");
	wxChartPanel *chartPanel = new wxChartPanel(this, wxID_ANY, chart, wxDefaultPosition, wxSize(100, 100));
	chartPanel->SetMinSize(wxSize(300, 300));
	sizer->Add(chartPanel, 1, wxEXPAND);

	SetSizerAndFit(sizer);
}

void LearningStateWindow::trainingPlanChanged(wxCommandEvent& event)
{
	AbstractTrainingPlan* trainingPlan = (*controller->getTrainingPlans())[event.GetSelection()].get();

}


void LearningStateWindow::selectionChanged(wxCommandEvent& event)
{

}

void LearningStateWindow::refreshTrainingPlans()
{
	trainingPlansChoice->Clear();
	for (auto network = controller->getTrainingPlans()->begin(); network != controller->getTrainingPlans()->end(); network++)
	{
		trainingPlansChoice->Append((*network)->getName());
	}
}
