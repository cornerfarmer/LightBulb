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
	/**
	 * \brief A sub app which makes it possible to manage learning rule preferences.
	 */
	class PreferencesController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding window.
		 */
		PreferencesWindow* window;
		/**
		 * \brief The training plan whose preferences should be shown.
		 */
		AbstractTrainingPlan* trainingPlan;
	public:
		/**
		 * \brief Creates the preference sub app.
		 * \param mainApp The main app.
		 * \param trainingPlan_ The training plan whose preferences should be shown.
		 * \param parent The parent window.
		 */
		PreferencesController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent);
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		PreferencesWindow& getWindow();
		/**
		 * \brief Returns the label of the sub app.
		 * \return The label.
		 */
		static std::string getLabel();
		/**
		 * \brief Returns all preference groups of the training plan.
		 * \return A vector of all preference elements.
		 */
		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceGroups();
		/**
		* \brief Returns the training plan whose preferences are managed by this controller.
		* \return The training plan.
		*/
		const AbstractTrainingPlan& getTrainingPlan();
	};
}

#endif
