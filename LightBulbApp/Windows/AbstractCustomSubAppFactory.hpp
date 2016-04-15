#pragma once

#ifndef _ABSTRACTCUSTOMSUBAPPFACTORY_H_
#define _ABSTRACTCUSTOMSUBAPPFACTORY_H_

// Library includes
#include <cstddef>
#include <string>

// Includes
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class AbstractCustomSubApp;
class AbstractTrainingPlan;

class AbstractCustomSubAppFactory
{
protected:
public:
	virtual AbstractCustomSubApp* createCustomSupApp(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent = NULL) = 0;
	virtual std::string getLabel() = 0;
};

#endif
