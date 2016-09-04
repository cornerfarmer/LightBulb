#pragma once

#ifndef _MOUNTAINCARFACTORY_H_
#define _MOUNTAINCARFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class TrainingPlanRepository;

class MountainCarFactory : public AbstractCustomSubAppFactory
{
protected:
public:
	AbstractCustomSubApp* createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
