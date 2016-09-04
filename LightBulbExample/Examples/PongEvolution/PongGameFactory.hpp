#pragma once

#ifndef _PONGGAMEFACTORY_H_
#define _PONGGAMEFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class TrainingPlanRepository;

class PongGameFactory : public AbstractCustomSubAppFactory
{
protected:
public:
	AbstractCustomSubApp* createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
