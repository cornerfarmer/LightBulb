#pragma once

#ifndef _PREFERENCESWINDOW_H_
#define _PREFERENCESWINDOW_H_

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

// Library include
#include <map>
#include "wx/collpane.h"

class wxCollapsiblePaneEvent;

namespace LightBulb
{
	// Forward declarations
	class PreferencesController;
	class DoublePreference;
	class AbstractPreference;
	class PreferenceGroup;

	class PreferencesWindow : public AbstractSubAppWindow
	{
	private:
		static const int stepCount;
		std::map<wxSlider*, wxTextCtrl*> textCtrlFromSlider;
		std::map<wxTextCtrl*, wxSlider*> sliderFromtextCtrl;
		std::map<wxSlider*, double> sliderStepSize;
		void setValueFromTextBox(wxCommandEvent& event, AbstractPreference& preference);
		void setValueFromCheckBox(wxCommandEvent& event, AbstractPreference& preference);
		void setValueFromChoice(wxCommandEvent& event, AbstractPreference& preference);
		void setValueFromSlider(wxCommandEvent& event, AbstractPreference& preference);
		double sliderValueToDouble(wxSlider& slider, DoublePreference& doublePreference, int value);
		double doubleToSliderValue(wxSlider& slider, DoublePreference& doublePreference, double value);
		wxSizer* createSlider(wxWindow& parent, std::string min, std::string max, std::string current, int currentStep, AbstractPreference& preference, int minStep, int maxStep, double stepSize = 0);
		wxSizer* createCheckBox(wxWindow& parent, std::string label, bool currentValue, AbstractPreference& preference);
		wxSizer* createChoice(wxWindow& parent, std::string label, int currentValueIndex, const std::vector<std::string>& choices, AbstractPreference& preference);
		wxCollapsiblePane* createCollapsiblePane(wxWindow& parent, PreferenceGroup& preferenceGroup, bool collapse);
		PreferencesController& getController();
		void refreshWindow(wxCollapsiblePaneEvent& event);
	public:
		PreferencesWindow(PreferencesController& controller_, AbstractWindow* parent = nullptr);
	};
}

#endif
