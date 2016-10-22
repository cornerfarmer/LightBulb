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
#include <wx/dataview.h>

namespace LightBulb
{
	enum
	{
		DATASET_REMOVE
	};

	wxDEFINE_EVENT(LSW_EVT_REFRESH_CHART, wxThreadEvent);

	LearningStateWindow::LearningStateWindow(LearningStateController& controller_, AbstractWindow& parent)
		:AbstractSubAppWindow(controller_, LearningStateController::getLabel(), parent)
	{
		controller = &controller_;

		Bind(LSW_EVT_REFRESH_CHART, wxThreadEventFunction(&LearningStateWindow::refreshChart), this);

		sizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* header = new wxBoxSizer(wxHORIZONTAL);

		header->Add(new wxStaticText(this, wxID_ANY, "Comparison dataset "), 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 5);
		comparisonDatasetChoice = new wxChoice(this, wxID_ANY);
		comparisonDatasetChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LearningStateWindow::comparisonDatasetChanged), this);
		header->Add(comparisonDatasetChoice, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 5);

		header->Add(new wxStaticText(this, wxID_ANY, "Refresh all "), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		refreshRateChoice = new wxComboBox(this, wxID_ANY);
		wxIntegerValidator<unsigned int> validator;
		validator.SetMin(1);
		validator.SetMax(1000000);
		refreshRateChoice->SetValue(std::to_string(getController().getRefreshRate()));
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
		header->Add(refreshRateChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		header->Add(new wxStaticText(this, wxID_ANY, " iterations."), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

		sizer->Add(header, 0, wxALL | wxALIGN_RIGHT, 7);

		wxBoxSizer* body = new wxBoxSizer(wxHORIZONTAL);

		dataSetsList = new wxDataViewListCtrl(this, wxID_ANY);
		dataSetsList->AppendTextColumn("Data sets");
		dataSetsList->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, wxObjectEventFunction(&LearningStateWindow::dataSetsListRightClick), this);

		body->Add(dataSetsList, 0, wxRIGHT | wxLEFT | wxEXPAND, 7);

		chartPanel = new wxChartPanel(this, wxID_ANY, nullptr, wxDefaultPosition, wxSize(100, 100));
		chartPanel->SetMinSize(wxSize(500, 300));

		body->Add(chartPanel, 1, wxEXPAND);

		sizer->Add(body, 1, wxEXPAND);

		wxBoxSizer* footer = new wxBoxSizer(wxHORIZONTAL);


		footer->Add(new wxStaticText(this, wxID_ANY, "Learning plan:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		trainingPlansChoice = new wxChoice(this, wxID_ANY);
		trainingPlansChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&LearningStateWindow::trainingPlanChanged), this);
		footer->Add(trainingPlansChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

		footer->Add(new wxStaticText(this, wxID_ANY, "Try:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		tryChoice = new wxChoice(this, wxID_ANY);
		footer->Add(tryChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

		footer->Add(new wxStaticText(this, wxID_ANY, "Dataset:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		dataSetChoice = new wxChoice(this, wxID_ANY);
		footer->Add(dataSetChoice, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);

		wxButton* button = new wxButton(this, wxID_ANY, "Add", wxDefaultPosition, wxSize(100, -1));
		footer->Add(button, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
		button->Bind(wxEVT_BUTTON, wxCommandEventFunction(&LearningStateWindow::addDataSet), this);

		sizer->Add(footer, 0, wxALL, 7);

		SetSizerAndFit(sizer);
	}

	void LearningStateWindow::trainingPlanChanged(wxCommandEvent& event)
	{
		getController().setSelectedTrainingPlan(event.GetSelection());

		dataSetChoice->Clear();
		std::vector<std::string> dataSetLabels = getController().getDataSetLabels();
		for (auto label = dataSetLabels.begin(); label != dataSetLabels.end(); label++)
		{
			dataSetChoice->Append(*label);
		}
		dataSetChoice->SetSelection(0);

		tryChoice->Clear();
		for (int i = 0; i < getController().getTryCount(); i++)
		{
			tryChoice->Append(std::to_string(i));
		}
		tryChoice->SetSelection(getController().getTryCount() - 1);

		refreshAfterChange(*sizer);
	}

	void LearningStateWindow::refreshRateChanged(wxCommandEvent& event)
	{
		try
		{
			getController().setRefreshRate(std::stoi(refreshRateChoice->GetValue().ToStdString()));
		}
		catch (std::invalid_argument e)
		{

		}
	}

	void LearningStateWindow::comparisonDatasetChanged(wxCommandEvent& event)
	{
		getController().setComparisonDataSetLabel(comparisonDatasetChoice->GetString(event.GetSelection()).ToStdString());
		wxThreadEvent evt;
		refreshChart(evt);
	}

	void LearningStateWindow::addDataSet(wxCommandEvent& event)
	{
		std::string label = getController().addDataSet(tryChoice->GetSelection(), dataSetChoice->GetSelection());

		refreshComparisonDatasetChoices();

		wxVector<wxVariant> data;
		data.push_back(label);
		dataSetsList->AppendItem(data);

		wxThreadEvent evt;
		refreshChart(evt);

		refreshAfterChange(*sizer);
	}

	void LearningStateWindow::refreshTrainingPlans()
	{
		trainingPlansChoice->Clear();
		for (auto network = getController().getTrainingPlans().begin(); network != getController().getTrainingPlans().end(); network++)
		{
			trainingPlansChoice->Append((*network)->getName());
		}
		refreshAfterChange(*sizer);
	}

	void LearningStateWindow::refreshChart(wxThreadEvent& event)
	{
		// first step: create plot
		XYPlot* plot = new XYPlot();
		// create dataset
		XYSimpleDataset *xyDataSet = new XYSimpleDataset();

		for (auto selectedDataSet = getController().getSelectedDataSets().begin(); selectedDataSet != getController().getSelectedDataSets().end(); selectedDataSet++)
		{
			DataSet& dataSet = selectedDataSet->getDataSet();
			if (dataSet.size() > 0)
			{
				if (getController().getComparisonDataSetLabel() != DEFAULT_COMP_DS)
				{
					DataSet dataSetCopy = dataSet;
					int comparisonIndex = 0;
					int dataSetIndex = 0;
					DataSet& comparisonDataSet = selectedDataSet->getDataSet(getController().getComparisonDataSetLabel());
					while (dataSetIndex < dataSetCopy.size() && comparisonIndex < comparisonDataSet.size())
					{
						if (dataSetCopy[dataSetIndex] == comparisonDataSet.at(comparisonIndex))
						{
							dataSetCopy[dataSetIndex] = comparisonDataSet.at(comparisonIndex + 1);
							dataSetIndex += 2;
							comparisonIndex += 2;
						}
						else if (dataSetCopy[dataSetIndex] < comparisonDataSet.at(comparisonIndex))
						{
							dataSetCopy[dataSetIndex] = comparisonDataSet.at(comparisonIndex + 1);
							dataSetIndex += 2;
						}
						else if (dataSetCopy[dataSetIndex] > comparisonDataSet.at(comparisonIndex))
						{
							comparisonIndex += 2;
						}
					}
					while (dataSetIndex < dataSetCopy.size())
					{
						if (dataSetIndex > 0)
							dataSetCopy[dataSetIndex] = dataSetCopy[dataSetIndex - 2];
						dataSetIndex += 2;
					}
					xyDataSet->AddSerie(&(dataSetCopy)[0], dataSetCopy.size() / 2);
				}
				else
				{
					// and add serie to it
					xyDataSet->AddSerie(&dataSet[0], dataSet.size() / 2);
				}

				// set line renderer to dataset
				xyDataSet->SetRenderer(new XYLineRenderer());

				xyDataSet->SetSerieName(xyDataSet->GetSerieCount() - 1, selectedDataSet->label);
			}
		}

		if (xyDataSet->GetSerieCount() > 0)
		{
			// create left and bottom number axes
			NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
			NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

			// optional: set axis titles
			leftAxis->SetTitle("Value");
			leftAxis->SetFixedBounds(std::min(xyDataSet->GetMinY(), 0.0), xyDataSet->GetMaxY());
			bottomAxis->SetTitle(getController().getComparisonDataSetLabel());

			// add axes and dataset to plot
			plot->AddObjects(xyDataSet, leftAxis, bottomAxis);

			// set legend
			plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

			// and finally create chart
			Chart* chart = new Chart(plot, getController().getSelectedTrainingPlan().getName());
			chartPanel->SetChart(chart);
		}
		else
		{
			chartPanel->SetChart(nullptr);
		}

		getController().refreshFinished();
	}

	void LearningStateWindow::dataSetsListRightClick(wxDataViewEvent& event)
	{
		if (event.GetItem())
		{
			wxMenu* popUpMenu = new wxMenu;
			popUpMenu->Append(new wxMenuItem(popUpMenu, DATASET_REMOVE, "Remove"));
			popUpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&LearningStateWindow::dataSetsPopUpMenuSelected), this);
			dataSetsList->PopupMenu(popUpMenu);
		}
	}

	void LearningStateWindow::dataSetsPopUpMenuSelected(wxCommandEvent& event)
	{
		if (event.GetId() == DATASET_REMOVE)
		{
			getController().removeDataSet(dataSetsList->GetSelectedRow());
			dataSetsList->DeleteItem(dataSetsList->GetSelectedRow());
			refreshComparisonDatasetChoices();
			wxThreadEvent evt;
			refreshChart(evt);
			refreshAfterChange(*sizer);
		}
	}

	void LearningStateWindow::refreshComparisonDatasetChoices()
	{
		std::string prevSelection = comparisonDatasetChoice->GetString(comparisonDatasetChoice->GetSelection()).ToStdString();
		int newSelection = 0;
		comparisonDatasetChoice->Clear();
		std::vector<std::string> possibilities = getController().getPossibleComparisonDatasetLabels();
		for (auto choice = possibilities.begin(); choice != possibilities.end(); choice++)
		{
			comparisonDatasetChoice->Append(*choice);
			if (*choice == prevSelection)
				newSelection = choice - possibilities.begin();
		}
		comparisonDatasetChoice->SetSelection(newSelection);
		getController().setComparisonDataSetLabel(possibilities[newSelection]);
	}

	LearningStateController& LearningStateWindow::getController()
	{
		return static_cast<LearningStateController&>(*controller);
	}
}