#pragma once

#ifndef _MOUNTAINCARFACTORY_H_
#define _MOUNTAINCARFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations

class MountainCarFactory : public LightBulb::AbstractCustomSubAppFactory
{
protected:
public:
	LightBulb::AbstractCustomSubApp* createCustomSupApp(LightBulb::AbstractMainApp& mainApp, LightBulb::AbstractTrainingPlan& trainingPlan, LightBulb::AbstractWindow& parent) const override;
	std::string getLabel() const override;
};

#endif
