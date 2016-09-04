#pragma once

#ifndef _LEARNINGSTATEFACTORY_H_
#define _LEARNINGSTATEFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class TrainingPlanRepository;

class LearningStateFactory : public AbstractSubAppFactory
{
protected:
	TrainingPlanRepository* trainingPlanRepository;
public:
	LearningStateFactory(TrainingPlanRepository* trainingPlanRepository_);
	AbstractSubApp* createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
