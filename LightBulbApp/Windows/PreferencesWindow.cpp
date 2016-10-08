// Includes
#include "Windows/PreferencesWindow.hpp"
#include "PreferencesController.hpp"
#include "TrainingPlans/Preferences/AbstractPreference.hpp"
#include <TrainingPlans/Preferences/DoublePreference.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/BooleanPreference.hpp>
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "wx/collpane.h"
#include "Learning/Evolution/FitnessSharingFitnessFunction.hpp"

namespace LightBulb
{
	class BooleanPreference;
	const int PreferencesWindow::stepCount = 1000;

	PreferencesController* PreferencesWindow::getController()
	{
		return static_cast<PreferencesController*>(controller);
	}

	PreferencesWindow::PreferencesWindow(PreferencesController* controller_, AbstractWindow* parent)
		:AbstractSubAppWindow(controller_, PreferencesController::getLabel(), parent)
	{
		wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

		wxScrolledWindow *sw = new wxScrolledWindow(this);
		wxSizer* scrollWinSizer = new wxBoxSizer(wxVERTICAL);

		for (auto preferenceGroup = controller_->getPreferenceGroups().begin(); preferenceGroup != controller_->getPreferenceGroups().end(); preferenceGroup++)
		{
			wxCollapsiblePane *collpane = new wxCollapsiblePane(sw, wxID_ANY, (*preferenceGroup)->getName() + ":", wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE | wxCP_NO_TLW_RESIZE);
			collpane->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, wxCollapsiblePaneEventFunction(&PreferencesWindow::refreshWindow), this);
			wxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
			for (auto preference = (*preferenceGroup)->getPreferences().begin(); preference != (*preferenceGroup)->getPreferences().end(); preference++)
			{
				if (!dynamic_cast<BooleanPreference*>(preference->get()))
					panelSizer->Add(new wxStaticText(collpane->GetPane(), wxID_ANY, (*preference)->getName()), 0, wxLEFT | wxRIGHT | wxUP, 7);

				if (dynamic_cast<DoublePreference*>(preference->get()))
				{
					DoublePreference* doublePreference = dynamic_cast<DoublePreference*>(preference->get());
					double stepSize = (doublePreference->getMax() - doublePreference->getMin()) / stepCount;
					int currentValue = (doublePreference->getValue() - doublePreference->getMin()) / stepSize;

					panelSizer->Add(createSlider(collpane->GetPane(), std::to_string(doublePreference->getMin()), std::to_string(doublePreference->getMax()), std::to_string(doublePreference->getValue()), currentValue, doublePreference, 0, stepCount, stepSize), 0, wxEXPAND);
				}
				else if (dynamic_cast<IntegerPreference*>(preference->get()))
				{
					IntegerPreference* integerPreference = dynamic_cast<IntegerPreference*>(preference->get());

					panelSizer->Add(createSlider(collpane->GetPane(), std::to_string(integerPreference->getMin()), std::to_string(integerPreference->getMax()), std::to_string(integerPreference->getValue()), integerPreference->getValue(), integerPreference, integerPreference->getMin(), integerPreference->getMax()), 0, wxEXPAND);
				}
				else if (dynamic_cast<BooleanPreference*>(preference->get()))
				{
					BooleanPreference* booleanPreference = dynamic_cast<BooleanPreference*>(preference->get());

					panelSizer->Add(createCheckBox(collpane->GetPane(), (*preference)->getName(), booleanPreference->getValue(), booleanPreference), 0, wxEXPAND);
				}
			}

			collpane->GetPane()->SetSizerAndFit(panelSizer);
			scrollWinSizer->Add(collpane, 0, wxGROW | wxEXPAND);

		}
		sw->SetSizerAndFit(scrollWinSizer);
		sw->SetScrollRate(10, 10);

		sizer->Add(sw, 1, wxEXPAND);
		sizer->SetMinSize(wxSize(500, 300));
		SetSizerAndFit(sizer);
	}


	void PreferencesWindow::refreshWindow(wxCollapsiblePaneEvent& event)
	{
		Layout();
	}


	wxSizer* PreferencesWindow::createSlider(wxWindow* parent, std::string min, std::string max, std::string current, int currentStep, AbstractPreference* preference, int minStep, int maxStep, double stepSize)
	{
		wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
		preferenceSizer->Add(new wxStaticText(parent, wxID_ANY, min), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		wxSlider* slider = new wxSlider(parent, wxID_ANY, currentStep, minStep, maxStep, wxDefaultPosition, wxDefaultSize);

		std::function<void(wxCommandEvent &)> slideHandler(bind(&PreferencesWindow::setValueFromSlider, this, std::placeholders::_1, preference));
		slider->Bind(wxEVT_SLIDER, slideHandler);

		preferenceSizer->Add(slider, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		sliderStepSize[slider] = stepSize;

		preferenceSizer->Add(new wxStaticText(parent, wxID_ANY, max), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		wxTextCtrl* textBox = new wxTextCtrl(parent, wxID_ANY);

		std::function<void(wxCommandEvent &)> textHandler(bind(&PreferencesWindow::setValueFromTextBox, this, std::placeholders::_1, preference));
		textBox->Bind(wxEVT_TEXT, textHandler);

		preferenceSizer->Add(textBox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);

		sliderFromtextCtrl[textBox] = slider;
		textCtrlFromSlider[slider] = textBox;

		textBox->SetValue(current);

		return preferenceSizer;
	}



	wxSizer* PreferencesWindow::createCheckBox(wxWindow* parent, std::string label, bool currentValue, AbstractPreference* preference)
	{
		wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
		wxCheckBox* checkBox = new wxCheckBox(parent, wxID_ANY, label);

		std::function<void(wxCommandEvent &)> checkHandler(bind(&PreferencesWindow::setValueFromCheckBox, this, std::placeholders::_1, preference));
		checkBox->Bind(wxEVT_CHECKBOX, checkHandler);
		preferenceSizer->Add(checkBox, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
		checkBox->SetValue(currentValue);

		return preferenceSizer;
	}

	void PreferencesWindow::setValueFromTextBox(wxCommandEvent& event, AbstractPreference* preference)
	{
		wxTextCtrl* textBox = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
		wxSlider* slider = sliderFromtextCtrl[textBox];
		if (dynamic_cast<DoublePreference*>(preference))
		{
			DoublePreference* doublePreference = static_cast<DoublePreference*>(preference);
			try
			{
				doublePreference->setValue(std::stod(event.GetString().ToStdString()));
			}
			catch (std::exception e)
			{
				doublePreference->reset();
			}

			slider->SetValue(doubleToSliderValue(slider, doublePreference, doublePreference->getValue()));
		}
		else
		{
			IntegerPreference* integerPreference = static_cast<IntegerPreference*>(preference);
			try
			{
				integerPreference->setValue(std::stoi(event.GetString().ToStdString()));
			}
			catch (std::exception e)
			{
				integerPreference->reset();
			}

			slider->SetValue(integerPreference->getValue());
		}
	}

	void PreferencesWindow::setValueFromCheckBox(wxCommandEvent& event, AbstractPreference* preference)
	{
		wxCheckBox* checkBox = dynamic_cast<wxCheckBox*>(event.GetEventObject());
		BooleanPreference* booleanPreference = static_cast<BooleanPreference*>(preference);
		booleanPreference->setValue(checkBox->GetValue());
	}

	void PreferencesWindow::setValueFromSlider(wxCommandEvent& event, AbstractPreference* preference)
	{
		wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
		if (dynamic_cast<DoublePreference*>(preference))
		{
			DoublePreference* doublePreference = static_cast<DoublePreference*>(preference);
			doublePreference->setValue(sliderValueToDouble(slider, doublePreference, slider->GetValue()));

			textCtrlFromSlider[slider]->SetValue(std::to_string(doublePreference->getValue()));
		}
		else
		{
			IntegerPreference* integerPreference = static_cast<IntegerPreference*>(preference);
			integerPreference->setValue(slider->GetValue());

			textCtrlFromSlider[slider]->SetValue(std::to_string(integerPreference->getValue()));
		}
	}

	double PreferencesWindow::sliderValueToDouble(wxSlider* slider, DoublePreference* doublePreference, int value)
	{
		return value * sliderStepSize[slider] + doublePreference->getMin();
	}

	double PreferencesWindow::doubleToSliderValue(wxSlider* slider, DoublePreference* doublePreference, double value)
	{
		return (value - doublePreference->getMin()) / sliderStepSize[slider];
	}
}
