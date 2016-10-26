#pragma once

#ifndef _ABSTRACTCUSTOMSUBAPPFACTORY_H_
#define _ABSTRACTCUSTOMSUBAPPFACTORY_H_

// Library includes
#include <cstddef>
#include <string>

// Includes
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCustomSubApp;
	class AbstractTrainingPlan;
	/**
	 * \brief A factory for custom sub apps.
	 */
	class AbstractCustomSubAppFactory
	{
	protected:
	public:
		virtual ~AbstractCustomSubAppFactory() {};
		/**
		 * \brief Creates the custom sub app.
		 * \param mainApp The main app which should control the main app.
		 * \param trainingPlan The corresponding training plan.
		 * \param parent The parent window.
		 * \return The created sub app.
		 */
		virtual AbstractCustomSubApp* createCustomSupApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan, AbstractWindow& parent) const = 0;
		/**
		 * \brief Returns the label of the sub app.
		 * \return The label.
		 */
		virtual std::string getLabel() const = 0;
	};
}

#endif
