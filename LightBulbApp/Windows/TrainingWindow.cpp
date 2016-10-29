// Includes
#include "Windows/TrainingWindow.hpp"
#include <wx/dataview.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/splitter.h>
#include <wx/artprov.h>
#include <wx/statline.h>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include "TrainingController.hpp"
#include <TrainingPlans/AbstractSingleNNTrainingPlan.hpp>
#include <wx/timer.h>

namespace LightBulb
{
	enum
	{
		TOOLBAR_START_TRAINING,
		TOOLBAR_PAUSE_TRAINING,
		TOOLBAR_PREFERENCES
	};

	enum
	{
		NETWORK_POPUP_SAVE
	};

	enum
	{
		FILE_LOAD_NN,
		FILE_LOAD_TP,
		FILE_SAVE_TS,
		FILE_LOAD_TS
	};

	BEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
		END_EVENT_TABLE()

		wxDEFINE_EVENT(TW_EVT_REFRESH_NN, wxCommandEvent);
	wxDEFINE_EVENT(TW_EVT_REFRESH_TPP, wxCommandEvent);
	wxDEFINE_EVENT(TW_EVT_REFRESH_TP, wxCommandEvent);
	wxDEFINE_EVENT(TW_EVT_REFRESH_ALL, wxCommandEvent);
	wxDEFINE_EVENT(TW_EVT_SAVE_TP, wxThreadEvent);
	wxDEFINE_EVENT(TW_EVT_SAVE_TS, wxThreadEvent);

	TrainingWindow::TrainingWindow(TrainingController& controller_)
		:AbstractWindow(controller_, "LightBulb")
	{
		controller = &controller_;
		processTrainingPlanSelection = nullptr;
		currentDetailObject = nullptr;
		customMenuVisible = false;

		Bind(TW_EVT_REFRESH_NN, wxCommandEventFunction(&TrainingWindow::refreshNeuralNetworks), this);
		Bind(TW_EVT_REFRESH_TP, wxCommandEventFunction(&TrainingWindow::refreshTrainingPlans), this);
		Bind(TW_EVT_REFRESH_TPP, wxCommandEventFunction(&TrainingWindow::refreshTrainingPlanPatterns), this);
		Bind(TW_EVT_REFRESH_ALL, wxCommandEventFunction(&TrainingWindow::refreshAllData), this);
		Bind(TW_EVT_SAVE_TP, wxThreadEventFunction(&TrainingWindow::saveTrainingPlan), this);
		Bind(TW_EVT_SAVE_TS, wxThreadEventFunction(&TrainingWindow::saveTrainingSession), this);

		createMenuBar();

		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxSplitterWindow* mainSplitterWindow = new wxSplitterWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
		wxSplitterWindow* centerSplitterWindow = new wxSplitterWindow(mainSplitterWindow, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
		wxSplitterWindow* rightSplitterWindow = new wxSplitterWindow(centerSplitterWindow, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
		rightSplitterWindow->SplitVertically(createTrainingColumn(*rightSplitterWindow), createRunningTrainingColumn(*rightSplitterWindow));
		rightSplitterWindow->SetSashGravity(0.5);

		centerSplitterWindow->SplitVertically(createNNColumn(*centerSplitterWindow), rightSplitterWindow);
		centerSplitterWindow->SetSashGravity(0.3333);

		mainSplitterWindow->SplitHorizontally(centerSplitterWindow, createDetailsPanel(*mainSplitterWindow));
		mainSplitterWindow->SetSashGravity(0.5);

		sizer->Add(mainSplitterWindow, 1, wxEXPAND);
		SetSizer(sizer);
		sizer->SetSizeHints(this);

		runTimeRefreshTimer = new wxTimer(this, wxID_ANY);
		Bind(wxEVT_TIMER, wxTimerEventFunction(&TrainingWindow::refreshTrainingPlanRunTimes), this);
		runTimeRefreshTimer->Start(1000);

		SetSize(1100, 700);
	}

	void TrainingWindow::fileMenuSelected(wxCommandEvent& event)
	{
		if (event.GetId() == FILE_LOAD_NN)
		{
			wxFileDialog openFileDialog(this, "Load neural network", "", "", "Neural network files (*.nn)|*.nn", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			if (openFileDialog.ShowModal() == wxID_CANCEL)
				return;

			getController().loadNeuralNetwork(openFileDialog.GetPath().ToStdString());
		}
		else if (event.GetId() == FILE_LOAD_TP)
		{
			wxFileDialog openFileDialog(this, "Load training plan", "", "", "Training plan files (*.tp)|*.tp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			if (openFileDialog.ShowModal() == wxID_CANCEL)
				return;

			getController().loadTrainingPlan(openFileDialog.GetPath().ToStdString());
		}
		else if (event.GetId() == FILE_LOAD_TS)
		{
			wxFileDialog openFileDialog(this, "Load training session", "", "", "Training session files (*.ts)|*.ts", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			if (openFileDialog.ShowModal() == wxID_CANCEL)
				return;

			getController().loadTrainingSession(openFileDialog.GetPath().ToStdString());
		}
		else if (event.GetId() == FILE_SAVE_TS)
		{
			Enable(false);
			Refresh();
			getController().saveTrainingSession();
		}
	}

	void TrainingWindow::trainingPlanMenuSelected(wxCommandEvent& event)
	{
		AbstractTrainingPlan* trainingPlan = getController().getTrainingPlans()[trainingPlanList->GetSelectedRow()].get();
		int factoryIndex = event.GetExtraLong();
		AbstractCustomSubAppFactory* selectedFactory = trainingPlan->getCustomSubApps()[factoryIndex].get();
		selectedFactory->createCustomSupApp(getController(), *trainingPlan, *this);
	}

	void TrainingWindow::neuralNetworkPopUpMenuSelected(wxCommandEvent& event)
	{
		if (event.GetId() == NETWORK_POPUP_SAVE)
		{
			wxFileDialog saveFileDialog(this, "Save neural network", "", "", "Neural network files (*.nn)|*.nn", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

			if (saveFileDialog.ShowModal() == wxID_CANCEL)
				return;

			getController().saveNeuralNetwork(saveFileDialog.GetPath().ToStdString(), neuralNetworkList->GetSelectedRow());
		}
	}

	void TrainingWindow::neuralNetworkListRightClick(wxDataViewEvent& event)
	{
		if (event.GetItem())
		{
			wxMenu* popUpMenu = new wxMenu;
			popUpMenu->Append(new wxMenuItem(popUpMenu, NETWORK_POPUP_SAVE, "Save network"));
			popUpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&TrainingWindow::neuralNetworkPopUpMenuSelected), this);
			neuralNetworkList->PopupMenu(popUpMenu);
		}
	}

	void TrainingWindow::trainingPlanPopUpMenuSelected(wxCommandEvent& event)
	{
		if (event.GetId() == NETWORK_POPUP_SAVE)
		{
			Enable(false);
			Refresh();
			getController().saveTrainingPlan(trainingPlanList->GetSelectedRow());
		}
	}


	void TrainingWindow::trainingPlanListRightClick(wxDataViewEvent& event)
	{
		if (event.GetItem())
		{
			wxMenu* popUpMenu = new wxMenu;
			popUpMenu->Append(new wxMenuItem(popUpMenu, NETWORK_POPUP_SAVE, "Save training plan"));
			popUpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&TrainingWindow::trainingPlanPopUpMenuSelected), this);
			neuralNetworkList->PopupMenu(popUpMenu);
		}
	}

	void TrainingWindow::trainingPlanNameChanged(wxDataViewEvent& event)
	{
		int row = trainingPlanList->ItemToRow(event.GetItem());
		std::string newName = event.GetValue();
		getController().setTrainingPlanName(row, newName);
		wxCommandEvent evt;
		refreshTrainingPlans(evt);
	}

	wxPanel* TrainingWindow::createNNColumn(wxWindow& parent)
	{
		wxPanel* panel = new wxPanel(&parent, wxID_ANY);

		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(new wxStaticText(panel, -1, "Neural networks"), 0, wxEXPAND | wxALL, 5);

		neuralNetworkList = new wxDataViewListCtrl(panel, wxID_ANY);
		neuralNetworkList->AppendTextColumn("Name", wxDATAVIEW_CELL_EDITABLE)->SetMinWidth(50);
		neuralNetworkList->AppendTextColumn("Size")->SetMinWidth(50);
		neuralNetworkList->AppendTextColumn("Creation date")->SetMinWidth(50);
		neuralNetworkList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectNeuralNetwork), this);
		neuralNetworkList->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, wxObjectEventFunction(&TrainingWindow::neuralNetworkListRightClick), this);
		neuralNetworkList->SetMinSize(wxSize(100, 100));

		sizer->Add(neuralNetworkList, 1, wxEXPAND, 0);
		panel->SetSizer(sizer);

		return panel;
	}


	void TrainingWindow::refreshNeuralNetworks(wxCommandEvent& event)
	{
		neuralNetworkList->DeleteAllItems();
		neuralNetworksChoice->Clear();
		for (auto network = getController().getNeuralNetworks().begin(); network != getController().getNeuralNetworks().end(); network++)
		{
			wxVector<wxVariant> data;
			data.push_back(wxVariant((*network)->getName()));
			data.push_back(wxVariant(getNeuralNetworkSizeAsString((*network)->getNetworkTopology().getNeuronCountsPerLayer())));
			std::time_t creationDate = (*network)->getCreationDate();
			data.push_back(wxVariant(std::asctime(std::localtime(&creationDate))));
			neuralNetworkList->AppendItem(data);
			neuralNetworksChoice->Append((*network)->getName());
			if (currentDetailObject == network->get())
				showDetailsOfNeuralNetwork(*network->get());
		}
		neuralNetworksChoice->Append("<Create new>");
		neuralNetworksChoice->SetSelection(getController().getNeuralNetworks().size());
	}

	wxPanel* TrainingWindow::createTrainingColumn(wxWindow& parent)
	{
		wxPanel* panel = new wxPanel(&parent, wxID_ANY);

		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(new wxStaticText(panel, -1, "Trainings"), 0, wxEXPAND | wxALL, 5);

		trainingPlanPatternList = new wxDataViewListCtrl(panel, wxID_ANY);
		trainingPlanPatternList->AppendTextColumn("Name")->SetMinWidth(50);
		trainingPlanPatternList->AppendTextColumn("Learning rate")->SetMinWidth(50);
		trainingPlanPatternList->AppendTextColumn("Description")->SetMinWidth(50);
		trainingPlanPatternList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectTrainingPlanPattern), this);
		trainingPlanPatternList->SetMinSize(wxSize(100, 100));

		sizer->Add(trainingPlanPatternList, 1, wxEXPAND, 0);
		panel->SetSizer(sizer);
		return panel;
	}


	void TrainingWindow::refreshTrainingPlanPatterns(wxCommandEvent& event)
	{
		trainingPlanPatternList->DeleteAllItems();
		trainingPlanPatternsChoice->Clear();
		for (auto trainingPlan = getController().getTrainingPlanPatterns().begin(); trainingPlan != getController().getTrainingPlanPatterns().end(); trainingPlan++)
		{
			wxVector<wxVariant> data;
			data.push_back(wxVariant((*trainingPlan)->getName()));
			data.push_back(wxVariant((*trainingPlan)->getLearningRuleName()));
			data.push_back(wxVariant((*trainingPlan)->getDescription()));
			trainingPlanPatternList->AppendItem(data);
			trainingPlanPatternsChoice->Append((*trainingPlan)->getName());
			if (currentDetailObject == trainingPlan->get())
				showDetailsOfTrainingPlanPattern(*trainingPlan->get());
		}
	}

	wxPanel* TrainingWindow::createRunningTrainingColumn(wxWindow& parent)
	{
		wxPanel* panel = new wxPanel(&parent, wxID_ANY);

		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(new wxStaticText(panel, -1, "Running trainings"), 0, wxEXPAND | wxALL, 5);

		trainingPlanList = new wxDataViewListCtrl(panel, wxID_ANY);
		trainingPlanList->AppendTextColumn("Training name", wxDATAVIEW_CELL_EDITABLE)->SetMinWidth(50);
		trainingPlanList->AppendTextColumn("State")->SetMinWidth(50);
		trainingPlanList->AppendTextColumn("Runtime")->SetMinWidth(50);
		trainingPlanList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, wxObjectEventFunction(&TrainingWindow::selectTrainingPlan), this);
		trainingPlanList->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, wxObjectEventFunction(&TrainingWindow::trainingPlanListRightClick), this);
		trainingPlanList->Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventFunction(&TrainingWindow::trainingPlanNameChanged), this);
		trainingPlanList->SetMinSize(wxSize(100, 100));

		sizer->Add(trainingPlanList, 1, wxEXPAND, 0);
		panel->SetSizer(sizer);
		return panel;
	}


	void TrainingWindow::refreshTrainingPlans(wxCommandEvent& event)
	{
		trainingPlanList->DeleteAllItems();
		for (auto trainingPlan = getController().getTrainingPlans().begin(); trainingPlan != getController().getTrainingPlans().end(); trainingPlan++)
		{
			wxVector<wxVariant> data;
			data.push_back(wxVariant((*trainingPlan)->getName()));
			data.push_back(wxVariant((*trainingPlan)->getStateAsString()));
			auto duration = (*trainingPlan)->getRunTime();
			data.push_back(wxVariant(getStringFromDuration(duration)));
			trainingPlanList->AppendItem(data);
			if (currentDetailObject == trainingPlan->get())
				showDetailsOfTrainingPlan(*trainingPlan->get());
			if (processTrainingPlanSelection == trainingPlan->get())
				showProcessOfTrainingPlan(*trainingPlan->get());
		}

	}

	void TrainingWindow::refreshAllData(wxCommandEvent& event)
	{
		refreshNeuralNetworks(event);
		refreshTrainingPlanPatterns(event);
		refreshTrainingPlans(event);
	}

	void TrainingWindow::saveTrainingPlan(wxThreadEvent& event)
	{
		int trainingPlanIndex = event.GetPayload<int>();
		wxFileDialog saveFileDialog(this, "Save training plan", "", getController().getTrainingPlans().at(trainingPlanIndex)->getName(), "Training plan files (*.tp)|*.tp", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		getController().saveTrainingPlan(saveFileDialog.GetPath().ToStdString(), trainingPlanIndex);

		Enable(true);
		Refresh();
	}

	void TrainingWindow::saveTrainingSession(wxThreadEvent& event)
	{
		wxFileDialog saveFileDialog(this, "Save training session", "", "", "Training session files (*.ts)|*.ts", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		getController().saveTrainingSession(saveFileDialog.GetPath().ToStdString());

		Enable(true);
		Refresh();
	}


	void TrainingWindow::addSubAppFactory(AbstractSubAppFactory& newSubAppFactory)
	{
		wxMenuItem* newItem = new wxMenuItem(windowsMenu, wxID_ANY, newSubAppFactory.getLabel());
		windowsMenu->Append(newItem);

	}

	wxPanel* TrainingWindow::createDetailsPanel(wxWindow& parent)
	{
		wxPanel* panel = new wxPanel(&parent, wxID_ANY);
		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

		wxSizer* commandSizer = new wxBoxSizer(wxVERTICAL);
		commandSizer->Add(new wxStaticText(panel, -1, "Commands"), 0, wxLEFT | wxBOTTOM, 10);
		commandSizer->AddStretchSpacer(1);

		wxSizer* processSizer = new wxBoxSizer(wxHORIZONTAL);

		neuralNetworksChoice = new wxChoice(panel, wxID_ANY);
		neuralNetworksChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&TrainingWindow::processSelecionHasChanged), this);
		processSizer->Add(neuralNetworksChoice);
		processSizer->Add(new wxStaticBitmap(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_FORWARD)), 0, wxALIGN_CENTRE_VERTICAL);
		trainingPlanPatternsChoice = new wxChoice(panel, wxID_ANY);
		trainingPlanPatternsChoice->Bind(wxEVT_CHOICE, wxCommandEventFunction(&TrainingWindow::processSelecionHasChanged), this);
		processSizer->Add(trainingPlanPatternsChoice);
		processSizer->SetSizeHints(panel);

		commandSizer->Add(processSizer, 0, wxEXPAND | wxALL, 20);
		commandSizer->AddStretchSpacer(1);

		processErrorText = new wxStaticText(panel, wxID_ANY, "");
		commandSizer->Add(processErrorText, 0, wxALL, 3);

		toolbar = new wxToolBar(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
		toolbar->AddTool(TOOLBAR_START_TRAINING, "Start", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
		toolbar->AddTool(TOOLBAR_PAUSE_TRAINING, "Pause", wxArtProvider::GetBitmap(wxART_DELETE));
		toolbar->AddTool(TOOLBAR_PREFERENCES, "Preferences", wxArtProvider::GetBitmap(wxART_EDIT));
		toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, false);
		toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TrainingWindow::startTraining), this, TOOLBAR_START_TRAINING);
		toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TrainingWindow::pauseTraining), this, TOOLBAR_PAUSE_TRAINING);
		toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TrainingWindow::showPreferences), this, TOOLBAR_PREFERENCES);
		toolbar->Realize();
		commandSizer->Add(toolbar);
		commandSizer->SetSizeHints(panel);
		sizer->Add(commandSizer, 0, wxEXPAND | wxTOP, 10);
		sizer->Add(new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVERTICAL), 0, wxEXPAND);

		wxSizer* detailsSizer = new wxBoxSizer(wxVERTICAL);
		detailsSizer->Add(new wxStaticText(panel, -1, "Details"), 0, wxBOTTOM, 10);
		detailsTextBox = new wxRichTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
		detailsTextBox->SetMinSize(wxSize(300, 50));
		detailsSizer->Add(detailsTextBox, 1, wxEXPAND);
		sizer->Add(detailsSizer, 1, wxEXPAND | wxALL, 10);
		detailsSizer->SetSizeHints(panel);

		panel->SetSizer(sizer);
		sizer->SetSizeHints(panel);
		return panel;
	}

	void TrainingWindow::validateSelectedProcess()
	{
		int neuralNetworkIndex = neuralNetworksChoice->GetSelection();
		int trainingPlanPatternIndex = trainingPlanPatternsChoice->GetSelection();
		AbstractSingleNNTrainingPlan* trainingPlan = dynamic_cast<AbstractSingleNNTrainingPlan*>(getController().getTrainingPlanPatterns()[trainingPlanPatternIndex].get());

		if (trainingPlan && neuralNetworkIndex < getController().getNeuralNetworks().size() && neuralNetworkIndex >= 0 && trainingPlanPatternIndex >= 0)
		{
			int requiredInputSize = trainingPlan->getRequiredInputSize();
			int requiredOutputSize = trainingPlan->getRequiredOutputSize();

			if (getController().getNeuralNetworks()[neuralNetworkIndex]->getNetworkTopology().getNeuronCountsPerLayer().front() != requiredInputSize ||
				getController().getNeuralNetworks()[neuralNetworkIndex]->getNetworkTopology().getNeuronCountsPerLayer().back() != requiredOutputSize)
			{
				processErrorText->SetLabel("The network must have " + std::to_string(requiredInputSize) + " input neurons and " + std::to_string(requiredOutputSize) + " output neurons!");
				toolbar->EnableTool(TOOLBAR_START_TRAINING, false);
			}
			else
			{
				if (getController().getNeuralNetworks()[neuralNetworkIndex]->getState() == NN_STATE_TRAINED)
				{
					processErrorText->SetLabel("The network gets already trained!");
					toolbar->EnableTool(TOOLBAR_START_TRAINING, false);
				}
				else
				{
					processErrorText->SetLabel("");
				}
			}
		}
		else
		{
			processErrorText->SetLabel("");
		}
		processErrorText->GetParent()->Layout();
	}

	void TrainingWindow::createMenuBar()
	{
		menubar = new wxMenuBar();
		wxMenu* file = new wxMenu;
		file->Append(wxID_OPEN);
		file->Append(new wxMenuItem(file, FILE_SAVE_TS, "Save training session"));
		file->Append(new wxMenuItem(file, FILE_LOAD_TS, "Load training session"));
		file->Append(new wxMenuItem(file, FILE_LOAD_NN, "Load a neural network"));
		file->Append(new wxMenuItem(file, FILE_LOAD_TP, "Load a training plan"));
		file->Append(wxID_SAVE);
		file->Append(wxID_EXIT);
		file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&TrainingWindow::fileMenuSelected), this);
		menubar->Append(file, "File");
		windowsMenu = new wxMenu();
		windowsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&TrainingWindow::addSubApp), this);
		menubar->Append(windowsMenu, "Windows");
		SetMenuBar(menubar);
	}

	void TrainingWindow::selectNeuralNetwork(wxDataViewEvent& event)
	{
		int row = getRowIndexOfItem(*neuralNetworkList, event.GetItem());
		if (row != -1)
		{
			removeCustomSubAppsMenu();
			showDetailsOfNeuralNetwork(*getController().getNeuralNetworks()[row].get());
			restoreDefaultProcessView();
			neuralNetworksChoice->Select(row);
			validateSelectedProcess();
		}
		else
		{
			removeCustomSubAppsMenu();
			clearDetails();
		}
	}

	void TrainingWindow::selectTrainingPlanPattern(wxDataViewEvent& event)
	{
		int row = getRowIndexOfItem(*trainingPlanPatternList, event.GetItem());
		if (row != -1) {
			removeCustomSubAppsMenu();
			showDetailsOfTrainingPlanPattern(*getController().getTrainingPlanPatterns()[row].get());
			restoreDefaultProcessView();
			trainingPlanPatternsChoice->Select(row);
			validateSelectedProcess();
		}
		else
		{
			removeCustomSubAppsMenu();
			clearDetails();
		}
	}

	void TrainingWindow::showProcessOfTrainingPlan(AbstractTrainingPlan& trainingPlan)
	{
		processTrainingPlanSelection = &trainingPlan;
		if (dynamic_cast<AbstractSingleNNTrainingPlan*>(&trainingPlan))
		{
			neuralNetworksChoice->Select(getController().getIndexOfNeuralNetwork(static_cast<AbstractSingleNNTrainingPlan&>(trainingPlan).getNeuralNetwork()));
		}
		trainingPlanPatternsChoice->Select(getController().getIndexOfTrainingPlanPattern(trainingPlan.getTrainingPlanPattern()));
		neuralNetworksChoice->Enable(false);
		trainingPlanPatternsChoice->Enable(false);
		toolbar->EnableTool(TOOLBAR_START_TRAINING, trainingPlan.isPaused());
		toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, trainingPlan.isRunning());
		toolbar->EnableTool(TOOLBAR_PREFERENCES, false);
		processErrorText->SetLabel("");
	}

	void TrainingWindow::restoreDefaultProcessView()
	{
		neuralNetworksChoice->Enable(true);
		trainingPlanPatternsChoice->Enable(true);
		toolbar->EnableTool(TOOLBAR_START_TRAINING, true);
		toolbar->EnableTool(TOOLBAR_PAUSE_TRAINING, false);
		toolbar->EnableTool(TOOLBAR_PREFERENCES, true);
		processTrainingPlanSelection = nullptr;
	}


	void TrainingWindow::removeCustomSubAppsMenu()
	{
		if (customMenuVisible)
		{
			menubar->Remove(menubar->GetMenuCount() - 1);
			customMenuVisible = false;
		}
	}

	void TrainingWindow::refreshTrainingPlanRunTimes(wxTimerEvent& event)
	{
		int trainingPlanIndex = 0;
		for (auto trainingPlan = getController().getTrainingPlans().begin(); trainingPlan != getController().getTrainingPlans().end(); trainingPlan++, trainingPlanIndex++)
		{
			if (trainingPlanIndex < trainingPlanList->GetItemCount()) {
				auto duration = (*trainingPlan)->getRunTime();
				trainingPlanList->SetValue(wxVariant(getStringFromDuration(duration)), trainingPlanIndex, 2);
			}
		}
	}

	std::string TrainingWindow::getStringFromDuration(std::chrono::duration<double> duration) const
	{
		auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
		duration -= hours;
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
		duration -= minutes;
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
		duration -= seconds;
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

		std::string output = "";
		if (hours.count() > 0)
			output += std::to_string(hours.count()) + "h ";
		if (minutes.count() > 0)
			output += std::to_string(minutes.count()) + "m ";
		if (seconds.count() > 0)
			output += std::to_string(seconds.count()) + "s ";

		output += std::to_string(milliseconds.count()) + "ms";
		return output;
	}

	TrainingController& TrainingWindow::getController()
	{
		return static_cast<TrainingController&>(*controller);
	}

	void TrainingWindow::close(wxCloseEvent& event)
	{
		event.Skip();
	}

	void TrainingWindow::showCustomSubAppsMenuForTrainingPlan(AbstractTrainingPlan& trainingPlan)
	{
		removeCustomSubAppsMenu();
		const std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>& customSubApps = trainingPlan.getCustomSubApps();
		if (customSubApps.size() > 0)
		{
			trainingPlanMenu = new wxMenu();
			for (auto customSubApp = customSubApps.begin(); customSubApp != customSubApps.end(); customSubApp++)
			{
				trainingPlanMenu->Append(new wxMenuItem(trainingPlanMenu, wxID_ANY, (*customSubApp)->getLabel()));
			}
			trainingPlanMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventFunction(&TrainingWindow::trainingPlanMenuSelected), this);
			menubar->Append(trainingPlanMenu, trainingPlan.getName());
			customMenuVisible = true;
		}
	}

	void TrainingWindow::selectTrainingPlan(wxDataViewEvent& event)
	{
		int row = getRowIndexOfItem(*trainingPlanList, event.GetItem());
		if (row != -1)
		{
			showDetailsOfTrainingPlan(*getController().getTrainingPlans()[row].get());
			showProcessOfTrainingPlan(*getController().getTrainingPlans()[row].get());
			showCustomSubAppsMenuForTrainingPlan(*getController().getTrainingPlans()[row].get());
		}
		else
		{
			removeCustomSubAppsMenu();
			clearDetails();
		}
	}

	void TrainingWindow::showDetailsOfNeuralNetwork(AbstractNeuralNetwork& neuralNetwork)
	{
		clearDetails();
		detailsTextBox->WriteText("Name: " + neuralNetwork.getName() + "\n");
		detailsTextBox->WriteText("Size: " + getNeuralNetworkSizeAsString(neuralNetwork.getNetworkTopology().getNeuronCountsPerLayer()) + "\n");
		std::time_t creationDate = neuralNetwork.getCreationDate();
		detailsTextBox->WriteText("Creation date: " + std::string(std::asctime(std::localtime(&creationDate))) + "\n");
		detailsTextBox->WriteText("State: " + neuralNetwork.getStateAsString() + "\n");
		currentDetailObject = &neuralNetwork;
	}

	void TrainingWindow::showDetailsOfTrainingPlanPattern(AbstractTrainingPlan& trainingPlan)
	{
		clearDetails();
		detailsTextBox->WriteText("Name: " + trainingPlan.getName() + "\n");
		detailsTextBox->WriteText("Learning rate: " + trainingPlan.getLearningRuleName() + "\n");
		detailsTextBox->WriteText("Description: " + trainingPlan.getDescription() + "\n");
		currentDetailObject = &trainingPlan;
	}

	void TrainingWindow::showDetailsOfTrainingPlan(AbstractTrainingPlan& trainingPlan)
	{
		clearDetails();
		detailsTextBox->WriteText("Name: " + trainingPlan.getName() + "\n");
		if (dynamic_cast<AbstractSingleNNTrainingPlan*>(&trainingPlan))
			detailsTextBox->WriteText("Network name: " + static_cast<AbstractSingleNNTrainingPlan&>(trainingPlan).getNeuralNetwork().getName() + "\n");
		detailsTextBox->WriteText("State: " + trainingPlan.getStateAsString() + "\n");
		detailsTextBox->WriteText("Seed: " + std::to_string(trainingPlan.getSeed()) + "\n");
		detailsTextBox->WriteText("Preferences:\n");
		for (auto preferenceGroup = trainingPlan.getPreferenceGroups().begin(); preferenceGroup != trainingPlan.getPreferenceGroups().end(); preferenceGroup++)
		{
			detailsTextBox->WriteText(" + " + (*preferenceGroup)->toString() + "\n");
		}


		currentDetailObject = &trainingPlan;
	}

	void TrainingWindow::clearDetails()
	{
		detailsTextBox->Clear();
		currentDetailObject = nullptr;
	}

	std::string TrainingWindow::getNeuralNetworkSizeAsString(const std::vector<unsigned int>& size) const
	{
		std::string neuronCountsPerLayerString = "";
		for (int i = 0; i < size.size(); i++)
		{
			if (i != 0)
				neuronCountsPerLayerString += "-";
			neuronCountsPerLayerString += std::to_string(size[i]);
		}
		return neuronCountsPerLayerString;
	}

	int TrainingWindow::getRowIndexOfItem(const wxDataViewListCtrl& list, const wxDataViewItem& item) const
	{
		return ((wxDataViewIndexListModel*)list.GetModel())->GetRow(item);
	}

	void TrainingWindow::startTraining(wxCommandEvent& event)
	{
		if (processTrainingPlanSelection == nullptr)
		{
			int neuralNetworkIndex = neuralNetworksChoice->GetSelection();
			int trainingPlanPatternIndex = trainingPlanPatternsChoice->GetSelection();
			if (neuralNetworkIndex != -1 && trainingPlanPatternIndex != -1)
			{
				getController().startTrainingPlanPattern(trainingPlanPatternIndex, neuralNetworkIndex);
			}
		}
		else
		{
			getController().resumeTrainingPlan(*processTrainingPlanSelection);
		}
	}

	void TrainingWindow::pauseTraining(wxCommandEvent& event)
	{
		if (processTrainingPlanSelection != nullptr)
		{
			getController().pauseTrainingPlan(*processTrainingPlanSelection);
		}
	}

	void TrainingWindow::showPreferences(wxCommandEvent& event)
	{
		int trainingPlanPatternIndex = trainingPlanPatternsChoice->GetSelection();
		getController().openPreferences(trainingPlanPatternIndex);
	}

	void TrainingWindow::processSelecionHasChanged(wxCommandEvent& event)
	{
		toolbar->EnableTool(TOOLBAR_START_TRAINING, true);
		validateSelectedProcess();
	}

	void TrainingWindow::addSubApp(wxCommandEvent& event)
	{
		int index = windowsMenu->GetMenuItems().IndexOf(windowsMenu->FindItem(event.GetId()));
		getController().addSubApp(index);
	}
}