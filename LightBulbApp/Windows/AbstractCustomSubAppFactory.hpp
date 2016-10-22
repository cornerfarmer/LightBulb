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

	class AbstractCustomSubAppFactory
	{
	protected:
	public:
		virtual ~AbstractCustomSubAppFactory() {};
		virtual AbstractCustomSubApp* createCustomSupApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan, AbstractWindow& parent) const = 0;
		virtual std::string getLabel() const = 0;
	};
}

#endif
