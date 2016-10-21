#pragma once
#ifndef _ABSTRACTCUSTOMSUBAPP_H_
#define _ABSTRACTCUSTOMSUBAPP_H_

// Includes
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractTrainingPlan;

	class AbstractCustomSubApp : public AbstractSubApp
	{
	protected:
		AbstractTrainingPlan* trainingPlan;
	public:
		AbstractCustomSubApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_);
	};
}

#endif
