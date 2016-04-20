// Includes
#include "Windows/PreferencesWindow.hpp"
#include "PreferencesController.hpp"
#include "TrainingPlans/AbstractPreference.hpp"
#include <TrainingPlans/DoublePreference.hpp>

const int PreferencesWindow::stepCount = 1000;

PreferencesWindow::PreferencesWindow(PreferencesController* controller_, AbstractWindow* parent)
	:AbstractWindow(PreferencesController::getLabel(), parent)
{
	controller = controller_;

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	for (auto preference = controller_->getPreferences().begin(); preference != controller_->getPreferences().end(); preference++)
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, (*preference)->getName()), 0, wxLEFT | wxRIGHT | wxUP, 7);
		if (dynamic_cast<DoublePreference*>(preference->get())) {
			DoublePreference* doublePreference = dynamic_cast<DoublePreference*>(preference->get());

			wxSizer* preferenceSizer = new wxBoxSizer(wxHORIZONTAL);
			preferenceSizer->Add(new wxStaticText(this, wxID_ANY, std::to_string(doublePreference->getMin())), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
			wxSlider* slider = new wxSlider(this, wxID_ANY, doublePreference->getValue(), 0, stepCount, wxDefaultPosition, wxDefaultSize);
			slider->Bind(wxEVT_SLIDER, wxCommandEventFunction(&PreferencesWindow::setDoubleValueFromSlider), this, wxID_ANY, wxID_ANY, (wxObject*)doublePreference);
			preferenceSizer->Add(slider, 1, wxALL | wxALIGN_CENTER_VERTICAL, 7);
			sliderStepSize[slider] = (doublePreference->getMax() - doublePreference->getMin()) / stepCount;

			preferenceSizer->Add(new wxStaticText(this, wxID_ANY, std::to_string(doublePreference->getMax())), 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);
			wxTextCtrl* textBox = new wxTextCtrl(this, wxID_ANY, std::to_string(doublePreference->getValue()));
			textBox->Bind(wxEVT_TEXT, wxCommandEventFunction(&PreferencesWindow::setDoubleValueFromTextBox), this, wxID_ANY, wxID_ANY, (wxObject*)doublePreference);
			preferenceSizer->Add(textBox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 7);

			sliderFromtextCtrl[textBox] = slider;
			textCtrlFromSlider[slider] = textBox;
			sizer->Add(preferenceSizer, 0, wxEXPAND);
		}
	}

	SetSizerAndFit(sizer);
}

void PreferencesWindow::setDoubleValueFromTextBox(wxCommandEvent& event)
{
	DoublePreference* doublePreference = (DoublePreference*)event.GetEventUserData();
	doublePreference->setValue(std::stod(event.GetString().ToStdString()));

	wxTextCtrl* textBox = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	sliderFromtextCtrl[textBox]->SetValue(doubleToSliderValue(sliderFromtextCtrl[textBox], doublePreference, doublePreference->getValue()));
}

void PreferencesWindow::setDoubleValueFromSlider(wxCommandEvent& event)
{
	DoublePreference* doublePreference = (DoublePreference*)event.GetEventUserData();
	wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
	doublePreference->setValue(sliderValueToDouble(slider, doublePreference, slider->GetValue()));
	
	textCtrlFromSlider[slider]->SetValue(std::to_string(doublePreference->getValue()));
}

double PreferencesWindow::sliderValueToDouble(wxSlider* slider, DoublePreference* doublePreference, int value)
{
	return value * sliderStepSize[slider] + doublePreference->getMin();
}

double PreferencesWindow::doubleToSliderValue(wxSlider* slider, DoublePreference* doublePreference, double value)
{
	return (value - doublePreference->getMin()) / sliderStepSize[slider];
}
