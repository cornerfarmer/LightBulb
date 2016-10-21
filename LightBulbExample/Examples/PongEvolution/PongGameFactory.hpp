#pragma once

#ifndef _PONGGAMEFACTORY_H_
#define _PONGGAMEFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations

class PongGameFactory : public LightBulb::AbstractCustomSubAppFactory
{
protected:
public:
	LightBulb::AbstractCustomSubApp* createCustomSupApp(LightBulb::AbstractMainApp& mainApp, LightBulb::AbstractTrainingPlan& trainingPlan, LightBulb::AbstractWindow* parent = nullptr) const override;
	std::string getLabel() const override;
};

#endif
