#pragma once

#ifndef _PREFERENCESWINDOW_H_
#define _PREFERENCESWINDOW_H_

// Library include
#include <map>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

namespace LightBulb
{
	// Forward declarations
	class PreferencesController;
	class DoublePreference;
	class AbstractPreference;

	class PreferencesWindow : public AbstractSubAppWindow
	{
	private:
		static const int stepCount;
		std::map<wxSlider*, wxTextCtrl*> textCtrlFromSlider;
		std::map<wxTextCtrl*, wxSlider*> sliderFromtextCtrl;
		std::map<wxSlider*, double> sliderStepSize;
		void setValueFromTextBox(wxCommandEvent& event, AbstractPreference* preference);
		void setValueFromCheckBox(wxCommandEvent& event, AbstractPreference* preference);
		void setValueFromSlider(wxCommandEvent& event, AbstractPreference* preference);
		double sliderValueToDouble(wxSlider* slider, DoublePreference* doublePreference, int value);
		double doubleToSliderValue(wxSlider* slider, DoublePreference* doublePreference, double value);
		wxSizer* createSlider(std::string min, std::string max, std::string current, int currentStep, AbstractPreference* preference, int minStep, int maxStep, double stepSize = 0);
		wxSizer* createCheckBox(std::string label, bool currentValue, AbstractPreference* preference);
		PreferencesController* getController();
	public:
		PreferencesWindow(PreferencesController* controller_, AbstractWindow* parent = NULL);
	};
}

#endif
