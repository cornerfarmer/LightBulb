#pragma once

#ifndef _LOGGERFACTORY_H_
#define _LOGGERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingPlanRepository;

	class LoggerFactory : public AbstractSubAppFactory
	{
	protected:
		TrainingPlanRepository* trainingPlanRepository;
	public:
		LoggerFactory(TrainingPlanRepository* trainingPlanRepository_);
		AbstractSubApp* createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) const override;
		const std::string& getLabel() const override;
	};
}

#endif
