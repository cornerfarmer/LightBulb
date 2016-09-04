#pragma once

#ifndef _NATUREFACTORY_H_
#define _NATUREFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class TrainingPlanRepository;

class NatureFactory : public AbstractCustomSubAppFactory
{
protected:
public:
	AbstractCustomSubApp* createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
