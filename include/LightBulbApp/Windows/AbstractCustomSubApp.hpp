#pragma once
#ifndef _ABSTRACTCUSTOMSUBAPP_H_
#define _ABSTRACTCUSTOMSUBAPP_H_

// Includes
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractTrainingPlan;
	/**
	 * \brief Describes a custom sub app which is used by one specific training plan.
	 */
	class AbstractCustomSubApp : public AbstractSubApp
	{
	protected:
		/**
		 * \brief The corresponding training plan.
		 */
		AbstractTrainingPlan* trainingPlan;
	public:
		/**
		 * \brief Creates the custom sub app.
		 * \param mainApp The main/parent app which should control the sub app.
		 * \param trainingPlan_ The corresponding training plan.
		 */
		AbstractCustomSubApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_);
	};
}

#endif
