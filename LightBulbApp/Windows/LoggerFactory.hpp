#pragma once

#ifndef _LOGGERFACTORY_H_
#define _LOGGERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class TrainingPlanRepository;

class LoggerFactory : public AbstractSubAppFactory
{
protected:
public:
	AbstractSubApp* createWindow(AbstractWindow* parent);
	std::string getLabel();
};

#endif
