#pragma once

#ifndef _PREFERENCESCONTROLLER_H_
#define _PREFERENCESCONTROLLER_H_

// Library includes
#include <vector>
#include <memory>

// Includes
#include "PreferencesWindow.hpp"
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractTrainingPlan;
	class AbstractPreferenceElement;

	class PreferencesController : public AbstractSubApp
	{
	private:
		std::unique_ptr<PreferencesWindow> window;
		AbstractTrainingPlan* trainingPlan;
	public:
		PreferencesController(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent = nullptr);
		PreferencesWindow* getWindow();
		static const std::string& getLabel();
		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceGroups();
	};
}

#endif
