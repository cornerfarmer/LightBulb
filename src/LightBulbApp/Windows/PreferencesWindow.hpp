#pragma once

#ifndef _PREFERENCESWINDOW_H_
#define _PREFERENCESWINDOW_H_

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

// Library include
#include <map>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/collpane.h"

class wxCollapsiblePaneEvent;

namespace LightBulb
{
	// Forward declarations
	class PreferencesController;
	class DoublePreference;
	class AbstractPreference;
	class PreferenceGroup;

	/**
	 * \brief The window the preference sub app.
	 */
	class PreferencesWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief Determines how many discrete steps a double slider should have.
		 */
		static const int stepCount;
		/**
		 * \brief A map which connects each slider with its corresponding text field.
		 */
		std::map<wxSlider*, wxTextCtrl*> textCtrlFromSlider;
		/**
		* \brief A map which connects each text field with its corresponding slider.
		*/
		std::map<wxTextCtrl*, wxSlider*> sliderFromtextCtrl;
		/**
		 * \brief Contains the step size for each slider.
		 */
		std::map<wxSlider*, double> sliderStepSize;
		/**
		 * \brief Sets the preference value from a text box.
		 * \param event The event data.
		 * \param preference The preference to change.
		 */
		void setValueFromTextBox(wxCommandEvent& event, AbstractPreference& preference);
		/**
		* \brief Sets the preference value from a check box.
		* \param event The event data.
		* \param preference The preference to change.
		*/
		void setValueFromCheckBox(wxCommandEvent& event, AbstractPreference& preference);
		/**
		* \brief Sets the preference value from a choice.
		* \param event The event data.
		* \param preference The preference to change.
		*/
		void setValueFromChoice(wxCommandEvent& event, AbstractPreference& preference);
		/**
		* \brief Sets the preference value from a slider.
		* \param event The event data.
		* \param preference The preference to change.
		*/
		void setValueFromSlider(wxCommandEvent& event, AbstractPreference& preference);
		/**
		 * \brief Gets the position of a slider as a double value.
		 * \param slider The slider.
		 * \param doublePreference The corresponding preferernce.
		 * \param value The slider position.
		 * \return The preference value
		 */
		double sliderValueToDouble(wxSlider& slider, DoublePreference& doublePreference, int value);
		/**
		 * \brief Gets the position of a slider from a double value.
		 * \param slider The slider.
		 * \param doublePreference The corresponding preferernce.
		 * \param value The preference value.
		 * \return The slider position.
		 */
		double doubleToSliderValue(wxSlider& slider, DoublePreference& doublePreference, double value);
		/**
		 * \brief Creates a new slider.
		 * \param parent The parent window.
		 * \param min The minimun allowed value as string.
		 * \param max The maximum allowed value as string.
		 * \param current The current value as string.
		 * \param currentStep The current value as step.
		 * \param preference The corresponding preference.
		 * \param minStep The minimun allowed value as step.
		 * \param maxStep The maximum allowed value as step.
		 * \param stepSize The step size.
		 * \return The new sizer which contains the new slider.
		 */
		wxSizer* createSlider(wxWindow& parent, std::string min, std::string max, std::string current, int currentStep, AbstractPreference& preference, int minStep, int maxStep, double stepSize = 0);
		/**
		 * \brief Creates a new checkbox.
		 * \param parent The parent window.
		 * \param label The label.
		 * \param currentValue The current value.
		 * \param preference The corresponding preference.
		 * \return The new sizer which contains the new check box.
		 */
		wxSizer* createCheckBox(wxWindow& parent, std::string label, bool currentValue, AbstractPreference& preference);
		/**
		 * \brief Creates a new choice
		 * \param parent The parent window.
		 * \param label The label.
		 * \param currentValueIndex The index of the current selected item.
		 * \param choices All possible choices.
		 * \param preference The corresponding preference.
		 * \return The new sizer which contains the new choice.
		 */
		wxSizer* createChoice(wxWindow& parent, std::string label, int currentValueIndex, const std::vector<std::string>& choices, AbstractPreference& preference);
		/**
		 * \brief Creates a collapsible pane which contains all prefernce controls of the given preference group.
		 * \param parent The parent window.
		 * \param preferenceGroup The corresponding preference group.
		 * \param collapse True if the pane should be collapsed by default.
		 * \return The new collapsible pane.
		 */
		wxCollapsiblePane* createCollapsiblePane(wxWindow& parent, PreferenceGroup& preferenceGroup, bool collapse);
		/**
		 * \brief Returns the corresponding controller.
		 * \return The controller.
		 */
		PreferencesController& getController();
		/**
		 * \brief Is called after a collapsible pane has been toggled.
		 * \details Refreshes the layout of the whole window.
		 * \param event The event data.
		 */
		void refreshWindow(wxCollapsiblePaneEvent& event);
	public:
		/**
		 * \brief Creates a new preference window.
		 * \param controller_ The corresponding controller.
		 * \param parent The parent window.
		 */
		PreferencesWindow(PreferencesController& controller_, AbstractWindow& parent);
	};
}

#endif
