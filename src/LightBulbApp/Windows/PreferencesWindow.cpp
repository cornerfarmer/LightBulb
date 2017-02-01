// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/PreferencesWindow.hpp"
#include "LightBulbApp/Windows/PreferencesController.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/AbstractPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/Learning/Evolution/FitnessSharingFitnessFunction.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/ChoicePreference.hpp"

namespace LightBulb
{
	class BooleanPreference;
	const int PreferencesWindow::stepCount = 1000;

	PreferencesController& PreferencesWindow::getController()
	{
		return static_cast<PreferencesController&>(*controller);
	}

	PreferencesWindow::PreferencesWindow(PreferencesController& controller_, AbstractWindow& parent)
		:AbstractSubAppWindow(controller_, PreferencesController::getLabel(), parent)
	{
		wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        collapsingActive = false;
		sw = new wxScrolledWindow(this);
		scrollWinSizer = new wxBoxSizer(wxVERTICAL);
		bool isFirst = true;

		for (auto preferenceGroup = controller_.getPreferenceGroups().begin(); preferenceGroup != controller_.getPreferenceGroups().end(); preferenceGroup++)
		{
			if (!static_cast<PreferenceGroup*>(preferenceGroup->get())->getPreferenceElements().empty())
			{
				scrollWinSizer->Add(createCollapsiblePane(*sw, static_cast<PreferenceGroup&>(*preferenceGroup->get()), !isFirst), 0, wxGROW | wxEXPAND);
				isFirst = false;
			}
		}
		sw->SetSizerAndFit(scrollWinSizer);
		sw->SetScrollRate(10, 10);

		sizer->Add(sw, 1, wxEXPAND);
		SetSizerAndFit(sizer);
		wxTopLevelWindowBase::SetMinSize(wxSize(450, 600));
		SetSize(wxSize(450, 600));
	}


	wxCollapsiblePane* PreferencesWindow::createCollapsiblePane(wxWindow& parent, PreferenceGroup& preferenceGroup, bool collapse)
	{
		wxCollapsiblePane *collpane = new wxCollapsiblePane(&parent, wxID_ANY, preferenceGroup.getName() + ":", wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE | wxCP_NO_TLW_RESIZE);
		collpane->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, wxCollapsiblePaneEventFunction(&PreferencesWindow::refreshWindow), this);
		collpane->Collapse(collapse);

		wxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
		for (auto preference = preferenceGroup.getPreferenceElements().begin(); preference != preferenceGroup.getPreferenceElements().end(); preference++)
		{
			if (PreferenceGroup* castedPreferenceGroup = dynamic_cast<PreferenceGroup*>(preference->get()))
			{
				panelSizer->Add(createCollapsiblePane(*collpane->GetPane(), *castedPreferenceGroup, true), 0, wxGROW | wxEXPAND);
			}
			else
			{
				if (!dynamic_cast<BooleanPreference*>(preference->get()))
					panelSizer->Add(new wxStaticText(collpane->GetPane(), wxID_ANY, (*preference)->getName()), 0, wxLEFT | wxRIGHT | wxUP, 7);

				if (DoublePreference* doublePreference = dynamic_cast<DoublePreference*>(preference->get()))
				{
					double stepSize = (doublePreference->getMax() - doublePreference->getMin()) / stepCount;
					int currentValue = (doublePreference->getValue() - doublePreference->getMin()) / stepSize;

					panelSizer->Add(createSlider(*collpane->GetPane(), std::to_string(doublePreference->getMin()), std::to_string(doublePreference->getMax()), std::to_string(doublePreference->getValue()), currentValue, *doublePreference, 0, stepCount, stepSize), 0, wxEXPAND);
				}
				else if (IntegerPreference* integerPreference = dynamic_cast<IntegerPreference*>(preference->get()))
				{
					panelSizer->Add(createSlider(*collpane->GetPane(), std::to_string(integerPreference->getMin()), std::to_string(integerPreference->getMax()), std::to_string(integerPreference->getValue()), integerPreference->getValue(), *integerPreference, integerPreference->getMin(), integerPreference->getMax()), 0, wxEXPAND);
				}
				else if (BooleanPreference* booleanPreference = dynamic_cast<BooleanPreference*>(preference->get()))
				{
					panelSizer->Add(createCheckBox(*collpane->GetPane(), (*preference)->getName(), booleanPreference->getValue(), *booleanPreference), 0, wxEXPAND);
				}
				else if (ChoicePreference* choicePreference = dynamic_cast<ChoicePreference*>(preference->get()))
				{
					panelSizer->Add(createChoice(*collpane->GetPane(), (*preference)->getName(), choicePreference->getValueAsIndex(), choicePreference->getChoices(), *choicePreference), 0, wxEXPAND);
				}
			}
		}

		collpane->GetPane()->SetSizerAndFit(panelSizer);

		return collpane;
	}

	void PreferencesWindow::refreshWindow(wxCollapsiblePaneEvent& event)
	{
        if (!collapsingActive) {
            collapsingActive = true;
            wxCollapsiblePane *collpane = static_cast<wxCollapsiblePane*>(event.GetEventObject());
            wxWindow* window = collpane->GetParent();

            int scroll = sw->GetScrollPos(wxVERTICAL);
            while (window->GetParent()) {
                if ((collpane = dynamic_cast<wxCollapsiblePane *>(window))) {
                    collpane->Collapse(true);
                    collpane->Collapse(false);
                }
                if (window->IsTopLevel())
                    break;
                window = window->GetParent();
            }
            Layout();
            sw->SetScrollPos(wxVERTICAL, scroll);
            collapsingActive = false;
        }
	}


	wxSizer* PreferencesWindow::createSlider(wxWindow& parent, std::string min, std::string max, std::string current, int currentStep, AbstractPreference& preference, int minStep, int maxStep, double stepSize)
	{
		wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
		preferenceSizer->Add(new wxStaticText(&parent, wxID_ANY, min), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		wxSlider* slider = new wxSlider(&parent, wxID_ANY, currentStep, minStep, maxStep, wxDefaultPosition, wxDefaultSize);

		std::function<void(wxCommandEvent &)> slideHandler(bind(&PreferencesWindow::setValueFromSlider, this, std::placeholders::_1, std::ref(preference)));
		slider->Bind(wxEVT_SLIDER, slideHandler);

		preferenceSizer->Add(slider, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		sliderStepSize[slider] = stepSize;

		preferenceSizer->Add(new wxStaticText(&parent, wxID_ANY, max), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		wxTextCtrl* textBox = new wxTextCtrl(&parent, wxID_ANY);

		std::function<void(wxCommandEvent &)> textHandler(bind(&PreferencesWindow::setValueFromTextBox, this, std::placeholders::_1, std::ref(preference)));
		textBox->Bind(wxEVT_TEXT, textHandler);

		preferenceSizer->Add(textBox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);

		sliderFromtextCtrl[textBox] = slider;
		textCtrlFromSlider[slider] = textBox;

		textBox->SetValue(current);

		return preferenceSizer;
	}



	wxSizer* PreferencesWindow::createCheckBox(wxWindow& parent, std::string label, bool currentValue, AbstractPreference& preference)
	{
		wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
		wxCheckBox* checkBox = new wxCheckBox(&parent, wxID_ANY, label);

		std::function<void(wxCommandEvent &)> checkHandler(bind(&PreferencesWindow::setValueFromCheckBox, this, std::placeholders::_1, std::ref(preference)));
		checkBox->Bind(wxEVT_CHECKBOX, checkHandler);
		preferenceSizer->Add(checkBox, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		checkBox->SetValue(currentValue);

		return preferenceSizer;
	}

	wxSizer* PreferencesWindow::createChoice(wxWindow& parent, std::string label, int currentValueIndex, const std::vector<std::string>& choices, AbstractPreference& preference)
	{
		wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
		wxChoice* choice = new wxChoice(&parent, wxID_ANY);
		for (auto choiceValue = choices.begin(); choiceValue != choices.end(); choiceValue++)
		{
			choice->AppendString(*choiceValue);
		}
		choice->SetSelection(currentValueIndex);

		std::function<void(wxCommandEvent &)> checkHandler(bind(&PreferencesWindow::setValueFromChoice, this, std::placeholders::_1, std::ref(preference)));
		choice->Bind(wxEVT_CHOICE, checkHandler);
		preferenceSizer->Add(choice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);

		return preferenceSizer;
	}

	void PreferencesWindow::setValueFromTextBox(wxCommandEvent& event, AbstractPreference& preference)
	{
		wxTextCtrl* textBox = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
		wxSlider* slider = sliderFromtextCtrl[textBox];
		if (dynamic_cast<DoublePreference*>(&preference))
		{
			DoublePreference& doublePreference = static_cast<DoublePreference&>(preference);
			try
			{
				doublePreference.setValue(std::stod(event.GetString().ToStdString()));
			}
			catch (std::exception e)
			{
				doublePreference.reset();
			}

			slider->SetValue(doubleToSliderValue(*slider, doublePreference, doublePreference.getValue()));
		}
		else
		{
			IntegerPreference& integerPreference = static_cast<IntegerPreference&>(preference);
			try
			{
				integerPreference.setValue(std::stoi(event.GetString().ToStdString()));
			}
			catch (std::exception e)
			{
				integerPreference.reset();
			}

			slider->SetValue(integerPreference.getValue());
		}
	}

	void PreferencesWindow::setValueFromCheckBox(wxCommandEvent& event, AbstractPreference& preference)
	{
		wxCheckBox* checkBox = dynamic_cast<wxCheckBox*>(event.GetEventObject());
		BooleanPreference& booleanPreference = static_cast<BooleanPreference&>(preference);
		booleanPreference.setValue(checkBox->GetValue());
	}

	void PreferencesWindow::setValueFromChoice(wxCommandEvent& event, AbstractPreference& preference)
	{
		wxChoice* choice = dynamic_cast<wxChoice*>(event.GetEventObject());
		ChoicePreference& choicePreference = static_cast<ChoicePreference&>(preference);
		choicePreference.setValueFromIndex(choice->GetSelection());
	}

	void PreferencesWindow::setValueFromSlider(wxCommandEvent& event, AbstractPreference& preference)
	{
		wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
		if (dynamic_cast<DoublePreference*>(&preference))
		{
			DoublePreference& doublePreference = static_cast<DoublePreference&>(preference);
			doublePreference.setValue(sliderValueToDouble(*slider, doublePreference, slider->GetValue()));

			textCtrlFromSlider[slider]->SetValue(std::to_string(doublePreference.getValue()));
		}
		else
		{
			IntegerPreference& integerPreference = static_cast<IntegerPreference&>(preference);
			integerPreference.setValue(slider->GetValue());

			textCtrlFromSlider[slider]->SetValue(std::to_string(integerPreference.getValue()));
		}
	}

	double PreferencesWindow::sliderValueToDouble(wxSlider& slider, DoublePreference& doublePreference, int value)
	{
		return value * sliderStepSize[&slider] + doublePreference.getMin();
	}

	double PreferencesWindow::doubleToSliderValue(wxSlider& slider, DoublePreference& doublePreference, double value)
	{
		return (value - doublePreference.getMin()) / sliderStepSize[&slider];
	}
}
