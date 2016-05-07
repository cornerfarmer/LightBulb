#pragma once

#ifndef _PREFERENCESWINDOW_H_
#define _PREFERENCESWINDOW_H_

// Library include
#include <map>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class PreferencesController;
class DoublePreference;

class PreferencesWindow : public AbstractWindow
{
private:
	static const int stepCount;
	PreferencesController* controller;
	std::map<wxSlider*, wxTextCtrl*> textCtrlFromSlider;
	std::map<wxTextCtrl*, wxSlider*> sliderFromtextCtrl;
	std::map<wxSlider*, double> sliderStepSize;
	void setValueFromTextBox(wxCommandEvent& event);
	void setValueFromSlider(wxCommandEvent& event);
	double sliderValueToDouble(wxSlider* slider, DoublePreference* doublePreference, int value);
	double doubleToSliderValue(wxSlider* slider, DoublePreference* doublePreference, double value);
	wxSizer* createSlider(std::string min, std::string max, std::string current, int currentStep, wxObject* preference, int minStep, int maxStep, double stepSize = 0);
public:
	PreferencesWindow(PreferencesController* controller_, AbstractWindow* parent = NULL);
};

#endif
