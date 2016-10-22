#pragma once

#ifndef _LEARNINGSTATEFACTORY_H_
#define _LEARNINGSTATEFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingPlanRepository;

	class LearningStateFactory : public AbstractSubAppFactory
	{
	protected:
		TrainingPlanRepository* trainingPlanRepository;
	public:
		LearningStateFactory(TrainingPlanRepository& trainingPlanRepository_);
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
