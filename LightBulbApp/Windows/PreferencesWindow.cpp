// Includes
#include "Windows/PreferencesWindow.hpp"
#include "PreferencesController.hpp"
#include "TrainingPlans/AbstractPreference.hpp"
#include <TrainingPlans/DoublePreference.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>

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

	for (auto preference = controller_->getPreferences().begin(); preference != controller_->getPreferences().end(); preference++)
	{
		if (!dynamic_cast<BooleanPreference*>(preference->get()))
			sizer->Add(new wxStaticText(this, wxID_ANY, (*preference)->getName()), 0, wxLEFT | wxRIGHT | wxUP, 7);

		if (dynamic_cast<DoublePreference*>(preference->get())) 
		{
			DoublePreference* doublePreference = dynamic_cast<DoublePreference*>(preference->get());
			double stepSize = (doublePreference->getMax() - doublePreference->getMin()) / stepCount;
			int currentValue = (doublePreference->getValue() - doublePreference->getMin()) / stepSize;

			sizer->Add(createSlider(std::to_string(doublePreference->getMin()), std::to_string(doublePreference->getMax()), std::to_string(doublePreference->getValue()), currentValue, (wxObject*)doublePreference, 0, stepCount, stepSize), 0, wxEXPAND);
		}
		else if (dynamic_cast<IntegerPreference*>(preference->get()))
		{
			IntegerPreference* integerPreference = dynamic_cast<IntegerPreference*>(preference->get());

			sizer->Add(createSlider(std::to_string(integerPreference->getMin()), std::to_string(integerPreference->getMax()), std::to_string(integerPreference->getValue()), integerPreference->getValue(), (wxObject*)integerPreference, integerPreference->getMin(), integerPreference->getMax()), 0, wxEXPAND);
		} 
		else if (dynamic_cast<BooleanPreference*>(preference->get()))
		{
			BooleanPreference* booleanPreference = dynamic_cast<BooleanPreference*>(preference->get());

			sizer->Add(createCheckBox((*preference)->getName(), booleanPreference->getValue(), (wxObject*)booleanPreference), 0, wxEXPAND);
		}
	}

	SetSizerAndFit(sizer);
}


wxSizer* PreferencesWindow::createSlider(std::string min, std::string max, std::string current, int currentStep, wxObject* preference, int minStep, int maxStep, double stepSize)
{
	wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
	preferenceSizer->Add(new wxStaticText(this, wxID_ANY, min), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
	wxSlider* slider = new wxSlider(this, wxID_ANY, currentStep, minStep, maxStep, wxDefaultPosition, wxDefaultSize);
	slider->Bind(wxEVT_SLIDER, wxCommandEventFunction(&PreferencesWindow::setValueFromSlider), this, wxID_ANY, wxID_ANY, preference);
	preferenceSizer->Add(slider, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
	sliderStepSize[slider] = stepSize;

	preferenceSizer->Add(new wxStaticText(this, wxID_ANY, max), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
	wxTextCtrl* textBox = new wxTextCtrl(this, wxID_ANY);
	textBox->Bind(wxEVT_TEXT, wxCommandEventFunction(&PreferencesWindow::setValueFromTextBox), this, wxID_ANY, wxID_ANY, preference);
	preferenceSizer->Add(textBox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);

	sliderFromtextCtrl[textBox] = slider;
	textCtrlFromSlider[slider] = textBox;

	textBox->SetValue(current);

	return preferenceSizer;
}



wxSizer* PreferencesWindow::createCheckBox(std::string label, bool currentValue, wxObject* preference)
{
	wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox* checkBox = new wxCheckBox(this, wxID_ANY, label);
	checkBox->Bind(wxEVT_CHECKBOX, wxCommandEventFunction(&PreferencesWindow::setValueFromCheckBox), this, wxID_ANY, wxID_ANY, preference);
	preferenceSizer->Add(checkBox, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
	checkBox->SetValue(currentValue);

	return preferenceSizer;
}

void PreferencesWindow::setValueFromTextBox(wxCommandEvent& event)
{
	wxTextCtrl* textBox = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	wxSlider* slider = sliderFromtextCtrl[textBox];
	if (sliderStepSize[slider] != 0)
	{
		DoublePreference* doublePreference = (DoublePreference*)(event.GetEventUserData());
		doublePreference->setValue(std::stod(event.GetString().ToStdString()));

		slider->SetValue(doubleToSliderValue(slider, doublePreference, doublePreference->getValue()));
	} 
	else
	{
		IntegerPreference* integerPreference = (IntegerPreference*)(event.GetEventUserData());
		integerPreference->setValue(std::stoi(event.GetString().ToStdString()));

		slider->SetValue(integerPreference->getValue());
	}
}

void PreferencesWindow::setValueFromCheckBox(wxCommandEvent& event)
{
	wxCheckBox* checkBox = dynamic_cast<wxCheckBox*>(event.GetEventObject());
	BooleanPreference* booleanPreference = (BooleanPreference*)(event.GetEventUserData());
	booleanPreference->setValue(checkBox->GetValue());
}

void PreferencesWindow::setValueFromSlider(wxCommandEvent& event)
{
	wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
	if (sliderStepSize[slider] != 0)
	{
		DoublePreference* doublePreference = (DoublePreference*)(event.GetEventUserData());
		doublePreference->setValue(sliderValueToDouble(slider, doublePreference, slider->GetValue()));

		textCtrlFromSlider[slider]->SetValue(std::to_string(doublePreference->getValue()));
	}
	else
	{
		IntegerPreference* integerPreference = (IntegerPreference*)(event.GetEventUserData());
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
