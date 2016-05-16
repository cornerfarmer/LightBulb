#pragma once

#ifndef _PREFERENCESCONTROLLER_H_
#define _PREFERENCESCONTROLLER_H_

// Library includes
#include <vector>
#include <memory>

// Includes
#include "PreferencesWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class AbstractTrainingPlan;
class AbstractPreference;

class PreferencesController : public AbstractSubApp
{
private:
	std::unique_ptr<PreferencesWindow> window;
	AbstractTrainingPlan* trainingPlan;
public:
	PreferencesController(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent = NULL);
	PreferencesWindow* getWindow();
	static std::string getLabel();
	std::vector<std::unique_ptr<AbstractPreference>>& getPreferences();
};

#endif
